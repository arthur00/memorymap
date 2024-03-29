/* Main code for remote server for GDB.
   Copyright (C) 1989, 1993, 1994, 1995, 1997, 1998, 1999, 2000, 2002, 2003,
   2004, 2005, 2006, 2011
   Free Software Foundation, Inc.

   This file is part of GDB.
   It has been modified to integrate it in valgrind

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

#include "server.h"
#include "regdef.h"
#include "pub_core_options.h"
#include "pub_core_translate.h"
#include "pub_core_mallocfree.h"

unsigned long cont_thread;
unsigned long general_thread;
unsigned long step_thread;
unsigned long thread_from_wait;
unsigned long old_thread_from_wait;

/* for a gdbserver integrated in valgrind, resuming the process consists
   in returning the control to valgrind.
   Then at the next error or break or ..., valgrind calls gdbserver again.
   A resume packet must then be built.
   resume_packet_needed records the fact that the next call to gdbserver
   must send a resume packet to gdb. */
static Bool resume_packet_needed = False;

VG_MINIMAL_JMP_BUF(toplevel);

/* Decode a qXfer read request.  Return 0 if everything looks OK,
   or -1 otherwise.  */

static
int decode_xfer_read (char *buf, char **annex, CORE_ADDR *ofs, unsigned int *len)
{
   /* Extract and NUL-terminate the annex.  */
   *annex = buf;
   while (*buf && *buf != ':')
      buf++;
   if (*buf == '\0')
      return -1;
   *buf++ = 0;

   /* After the read/write marker and annex, qXfer looks like a
      traditional 'm' packet.  */
   decode_m_packet (buf, ofs, len);

   return 0;
}

/* Write the response to a successful qXfer read.  Returns the
   length of the (binary) data stored in BUF, corresponding
   to as much of DATA/LEN as we could fit.  IS_MORE controls
   the first character of the response.  */
static
int write_qxfer_response (char *buf, unsigned char *data, int len, int is_more)
{
   int out_len;

   if (is_more)
      buf[0] = 'm';
   else
      buf[0] = 'l';

   return remote_escape_output (data, len, (unsigned char *) buf + 1, &out_len,
                                PBUFSIZ - POVERHSIZ - 1) + 1;
}

static Bool initial_valgrind_sink_saved = False;
/* True <=> valgrind log sink saved in initial_valgrind_sink */
static OutputSink initial_valgrind_sink;

static Bool command_output_to_log = False;
/* True <=> command output goes to log instead of gdb */

void reset_valgrind_sink(char *info)
{
   if (VG_(log_output_sink).fd != initial_valgrind_sink.fd
       && initial_valgrind_sink_saved) {
      VG_(log_output_sink).fd = initial_valgrind_sink.fd;
      VG_(umsg) ("Reset valgrind output to log (%s)\n",
                 (info = NULL ? "" : info));
   }
}

static
void kill_request (char *msg)
{
   VG_(umsg) ("%s", msg);
   remote_close();
   VG_(exit) (0);
}

/* handle_gdb_valgrind_command handles the provided mon string command.
   If command is recognised, return 1 else return 0.
   Note that in case of ambiguous command, 1 is returned.

   *sink_wanted_at_return is modified if one of the commands 
   'vg.set *_output' is handled.
*/
static
int handle_gdb_valgrind_command (char* mon, OutputSink* sink_wanted_at_return)
{
   UWord ret = 0;
   char s[strlen(mon)+1]; /* copy for strtok_r */
   char* wcmd;
   Char* ssaveptr;
   char* endptr;
   int   kwdid;
   int int_value;

   vg_assert (initial_valgrind_sink_saved);

   strcpy (s, mon);
   wcmd = strtok_r (s, " ", &ssaveptr);
   /* NB: if possible, avoid introducing a new command below which
      starts with the same 4 first letters as an already existing
      command. This ensures a shorter abbreviation for the user. */
   switch (VG_(keyword_id) ("help vg.set vg.info vg.wait vg.kill vg.translate",
                            wcmd, kwd_report_duplicated_matches)) {
   case -2:
      ret = 1;
      break;
   case -1: 
      break;
   case  0: /* help */
      ret = 1;
      wcmd = strtok_r (NULL, " ", &ssaveptr);
      if (wcmd == NULL) {
         int_value = 0;
      } else {
         switch (VG_(keyword_id) ("debug", wcmd, kwd_report_all)) {
         case -2: int_value = 0; break;
         case -1: int_value = 0; break;
         case  0: int_value = 1; break;
         default: tl_assert (0);
         }
      }

      VG_(gdb_printf) (
"general valgrind monitor commands:\n"
"  help [debug]             : monitor command help. With debug: + debugging commands\n"
"  vg.wait [<ms>]           : sleep <ms> (default 0) then continue\n"
"  vg.info all_errors       : show all errors found so far\n"
"  vg.info last_error       : show last error found\n"
"  vg.info n_errs_found     : show the nr of errors found so far\n"
"  vg.kill                  : kill the Valgrind process\n"
"  vg.set gdb_output        : set valgrind output to gdb\n"
"  vg.set log_output        : set valgrind output to log\n"
"  vg.set mixed_output      : set valgrind output to log, interactive output to gdb\n"
"  vg.set vgdb-error <errornr> : debug me at error >= <errornr> \n");
      if (int_value) { VG_(gdb_printf) (
"debugging valgrind internals monitor commands:\n"
"  vg.info gdbserver_status : show gdbserver status\n"
"  vg.info memory           : show valgrind heap memory stats\n"
"  vg.set debuglog <level>  : set valgrind debug log level to <level>\n"
"  vg.translate <addr> [<traceflags>]  : debug translation of <addr> with <traceflags>\n"
"    (default traceflags 0b00100000 : show after instrumentation)\n"
"   An additional flag  0b100000000 allows to show gdbserver instrumentation\n");
      }
      break;
   case  1: /* vg.set */
      ret = 1;
      wcmd = strtok_r (NULL, " ", &ssaveptr);
      switch (kwdid = VG_(keyword_id) 
              ("vgdb-error debuglog gdb_output log_output mixed_output",
               wcmd, kwd_report_all)) {
      case -2:
      case -1: 
         break;
      case 0: /* vgdb-error */
      case 1: /* debuglog */
         wcmd = strtok_r (NULL, " ", &ssaveptr);
         if (wcmd == NULL) {
            int_value = 0;
            endptr = "empty"; /* to report an error below */
         } else {
            int_value = strtol (wcmd, &endptr, 10);
         }
         if (*endptr != '\0') {
            VG_(gdb_printf) ("missing or malformed integer value\n");
         } else if (kwdid == 0) {
            VG_(gdb_printf) ("vgdb-error value changed from %d to %d\n",
                             VG_(dyn_vgdb_error), int_value);
            VG_(dyn_vgdb_error) = int_value;
         } else if (kwdid == 1) {
            VG_(gdb_printf) ("debuglog value changed from %d to %d\n",
                             VG_(debugLog_getLevel)(), int_value);
            VG_(debugLog_startup) (int_value, "gdbsrv");
         } else {
            vg_assert (0);
         }
         break;
      case 2: /* gdb_output */
         (*sink_wanted_at_return).fd = -2;
         command_output_to_log = False;
         VG_(gdb_printf) ("valgrind output will go to gdb\n");
         break;
      case 3: /* log_output */
         (*sink_wanted_at_return).fd = initial_valgrind_sink.fd;
         command_output_to_log = True;
         VG_(gdb_printf) ("valgrind output will go to log\n");
         break;
      case 4: /* mixed output */
         (*sink_wanted_at_return).fd = initial_valgrind_sink.fd;
         command_output_to_log = False;
         VG_(gdb_printf)
            ("valgrind output will go to log, interactive output will go to gdb\n");
         break;
      default:
         vg_assert (0);
      }
      break;
   case  2: /* vg.info */ {
      ret = 1;
      wcmd = strtok_r (NULL, " ", &ssaveptr);
      switch (kwdid = VG_(keyword_id) 
              ("all_errors n_errs_found last_error gdbserver_status memory",
               wcmd, kwd_report_all)) {
      case -2:
      case -1: 
         break;
      case 0: // all_errors
         // A verbosity of minimum 2 is needed to show the errors.
         VG_(show_all_errors)(/* verbosity */ 2, /* xml */ False);
         break;
      case  1: // n_errs_found
         VG_(gdb_printf) ("n_errs_found %d (vgdb-error %d)\n", 
                          VG_(get_n_errs_found) (),
                          VG_(dyn_vgdb_error));
         break;
      case 2: // last_error
         VG_(show_last_error)();
         break;
      case  3: // gdbserver_status
         VG_(gdbserver_status_output)();
         break;
      case  4: /* memory */
         VG_(print_all_arena_stats) ();
         if (VG_(clo_profile_heap))
            VG_(print_arena_cc_analysis) ();
         ret = 1;
         break;
      default:
         vg_assert(0);
      }
      break;
   }
   case  3: /* vg.wait */
      wcmd = strtok_r (NULL, " ", &ssaveptr);
      if (wcmd != NULL) {
         int_value = strtol (wcmd, &endptr, 10);
         VG_(gdb_printf) ("gdbserver: continuing in %d ms ...\n", int_value);
         VG_(poll)(NULL, 0, int_value);
      }
      VG_(gdb_printf) ("gdbserver: continuing after wait ...\n");
      ret = 1;
      break;
   case  4: /* vg.kill */
      kill_request ("monitor command request to kill this process\n");
      break;
   case  5: { /* vg.translate */
      Addr address;
      SizeT verbosity = 0x20;
      
      ret = 1;

      VG_(strtok_get_address_and_size) (&address, &verbosity, &ssaveptr);
      if (address != (Addr) 0 || verbosity != 0) {
         /* we need to force the output to log for the translation trace,
            as low level VEX tracing cannot be redirected to gdb. */
         int saved_command_output_to_log = command_output_to_log;
         int saved_fd = VG_(log_output_sink).fd;
         Bool single_stepping_on_entry = valgrind_single_stepping();
         int vex_verbosity = verbosity & 0xff;
         VG_(log_output_sink).fd = initial_valgrind_sink.fd;
         if ((verbosity & 0x100) && !single_stepping_on_entry) {
            valgrind_set_single_stepping(True); 
            // to force gdbserver instrumentation.
         }
#        if defined(VGA_arm)
         // on arm, we need to (potentially) convert this address
         // to the thumb form.
         address = thumb_pc (address);
#        endif

         VG_(translate) ( 0 /* dummy ThreadId; irrelevant due to debugging*/,
                          address,
                          /*debugging*/True, 
                          (Int) vex_verbosity,
                          /*bbs_done*/0,
                          /*allow redir?*/True);
         if ((verbosity & 0x100) && !single_stepping_on_entry) {
            valgrind_set_single_stepping(False);
            // reset single stepping.
         }
         command_output_to_log = saved_command_output_to_log;
         VG_(log_output_sink).fd = saved_fd;
      }
      break;
   }

   default:
      vg_assert (0);
   }
   return ret;
}

/* handle_gdb_monitor_command handles the provided mon string command,
   which can be either a "standard" valgrind monitor command
   or a tool specific monitor command.
   If command recognised, return 1 else return 0.
   Note that in case of ambiguous command, 1 is returned.
*/
static
int handle_gdb_monitor_command (char* mon)
{
   UWord ret = 0;
   UWord tool_ret = 0;
   // initially, we assume that when returning, the desired sink is the
   // one we have when entering. It can however be changed by the standard
   // valgrind command handling.
   OutputSink sink_wanted_at_return = VG_(log_output_sink);

   if (!initial_valgrind_sink_saved) {
      /* first time we enter here, we save the valgrind default log sink */
      initial_valgrind_sink = sink_wanted_at_return;
      initial_valgrind_sink_saved = True;
   }

   if (!command_output_to_log)
      VG_(log_output_sink).fd = -2; /* redirect to monitor_output */

   ret = handle_gdb_valgrind_command (mon, &sink_wanted_at_return);

   /* Even if command was recognised by valgrind core, we call the
      tool command handler : this is needed to handle help command
      and/or to let the tool do some additional processing of a
      valgrind standard command. Note however that if valgrind
      recognised the command, we will always return success. */
   if (VG_(needs).client_requests) {
      /* If the tool reports an error when handling a monitor command,
         we need to avoid calling gdbserver during this command
         handling. So, we temporarily set VG_(dyn_vgdb_error) to
         a huge value to ensure m_errormgr.c does not call gdbserver. */
      Int save_dyn_vgdb_error = VG_(dyn_vgdb_error);
      UWord arg[2];
      VG_(dyn_vgdb_error) = 999999999;
      arg[0] = (UWord) VG_USERREQ__GDB_MONITOR_COMMAND;
      arg[1] = (UWord) mon;
      VG_TDICT_CALL(tool_handle_client_request, VG_(running_tid), arg,
                    &tool_ret);
      VG_(dyn_vgdb_error) = save_dyn_vgdb_error;
   }

   /* restore or set the desired output */
   VG_(log_output_sink).fd = sink_wanted_at_return.fd;
   if (ret | tool_ret)
      return 1;
   else
      return 0;
}


/* Handle all of the extended 'Q' packets.  */
static
void handle_set (char *arg_own_buf, int *new_packet_len_p)
{
   if (strcmp ("QStartNoAckMode", arg_own_buf) == 0) {
      noack_mode = True;
      write_ok (arg_own_buf);
      return;
   }

   if (strncmp ("QPassSignals:", arg_own_buf, 13) == 0) {
      int i;
      char *from, *to;
      char *end = arg_own_buf + strlen(arg_own_buf);
      CORE_ADDR sig;
      for (i = 0; i < TARGET_SIGNAL_LAST; i++)
         pass_signals[i] = 0;
     
      from = arg_own_buf + 13;
      while (from < end) {
         to = strchr(from, ';');
         if (to == NULL) to = end;
         decode_address (&sig, from, to - from);
         pass_signals[(int)sig] = 1;
         dlog(1, "pass_signal %d\n", (int)sig);
         from = to;
         if (*from == ';') from++;
      }
      write_ok (arg_own_buf);
      return;
   }
   /* Otherwise we didn't know what packet it was.  Say we didn't
      understand it.  */
   arg_own_buf[0] = 0;
}

/* Handle all of the extended 'q' packets.  */
static
void handle_query (char *arg_own_buf, int *new_packet_len_p)
{
   static struct inferior_list_entry *thread_ptr;

   /* qRcmd, monitor command handling.  */
   if (strncmp ("qRcmd,", arg_own_buf, 6) == 0) {
      char *p = arg_own_buf + 6;
      int cmdlen = strlen(p)/2;
      char cmd[cmdlen+1];
      
      if (unhexify (cmd, p, cmdlen) != cmdlen) {
         write_enn (arg_own_buf);
         return;
      }
      cmd[cmdlen] = '\0';
       
      if (handle_gdb_monitor_command (cmd)) {
         /* In case the command is from a standalone vgdb,
            connection will be closed soon => flush the output. */
         VG_(message_flush) ();
         write_ok (arg_own_buf);
         return;
      } else {
         /* cmd not recognised */
         VG_(gdb_printf) 
            ("command '%s' not recognised\n"
             "In gdb,     try 'monitor help'\n"
             "In a shell, try 'vgdb help'\n",
             cmd);
         write_ok (arg_own_buf);
         return;
      }
   }

   /* provide some valgrind specific info in return to qThreadExtraInfo. */
   if (strncmp ("qThreadExtraInfo,", arg_own_buf, 17) == 0) {
      unsigned long gdb_id;
      struct thread_info *ti;
      ThreadState *tst;
      char status[100];
      
      gdb_id = strtoul (&arg_own_buf[17], NULL, 16);
      ti = gdb_id_to_thread (gdb_id);
      if (ti != NULL) {
         tst = (ThreadState *) inferior_target_data (ti);
         /* Additional info is the tid and the thread status. */
         VG_(snprintf) (status, sizeof(status), "tid %d %s",
                        tst->tid, 
                        VG_(name_of_ThreadStatus)(tst->status));
         hexify (arg_own_buf, status, strlen(status));
         return;
      } else {
         write_enn (arg_own_buf);
         return;
      }
   }
   
   if (strcmp ("qAttached", arg_own_buf) == 0) {
      /* tell gdb to always detach, never kill the process */
      arg_own_buf[0] = '1';
      arg_own_buf[1] = 0;
      return;
   }

   if (strcmp ("qSymbol::", arg_own_buf) == 0) {
      /* We have no symbol to read. */
      write_ok (arg_own_buf);
      return;
   }

   if (strcmp ("qfThreadInfo", arg_own_buf) == 0) {
      thread_ptr = all_threads.head;
      VG_(sprintf) (arg_own_buf, "m%x", 
                    thread_to_gdb_id ((struct thread_info *)thread_ptr));
      thread_ptr = thread_ptr->next;
      return;
   }

   if (strcmp ("qsThreadInfo", arg_own_buf) == 0) {
      if (thread_ptr != NULL) {
         VG_(sprintf) (arg_own_buf, "m%x", 
                       thread_to_gdb_id ((struct thread_info *)thread_ptr));
         thread_ptr = thread_ptr->next;
         return;
      } else {
         VG_(sprintf) (arg_own_buf, "l");
         return;
      }
   }

   if ( ((*the_target->target_xml)() != NULL 
         || (*the_target->shadow_target_xml)() != NULL)
        && strncmp ("qXfer:features:read:", arg_own_buf, 20) == 0) {
      CORE_ADDR ofs;
      unsigned int len, doc_len;
      char *annex = NULL;
      // First, the annex is extracted from the packet received.
      // Then, it is replaced by the corresponding file name.
      int fd;

      /* Grab the annex, offset, and length.  */
      if (decode_xfer_read (arg_own_buf + 20, &annex, &ofs, &len) < 0) {
         strcpy (arg_own_buf, "E00");
         return;
      }
      
      if (strcmp (annex, "target.xml") == 0) {
         annex = NULL; // to replace it by the corresponding filename.

         /* If VG_(clo_vgdb_shadow_registers), try to use
            shadow_target_xml. Fallback to target_xml
            if not defined. */
         if (VG_(clo_vgdb_shadow_registers)) {
            annex = (*the_target->shadow_target_xml)();
            if (annex != NULL)
               /* Ensure the shadow registers are initialized. */
               initialize_shadow_low(True);
         }
         if (annex == NULL)
            annex = (*the_target->target_xml)();
         if (annex == NULL) {
            strcpy (arg_own_buf, "E00");
            return;
         }
      }

      {
         char doc[VG_(strlen)(VG_(libdir)) + 1 + VG_(strlen)(annex)];
         struct vg_stat stat_doc;
         char toread[len];
         int len_read;

         VG_(sprintf)(doc, "%s/%s", VG_(libdir), annex);
         fd = VG_(fd_open) (doc, VKI_O_RDONLY, 0);
         if (fd == -1) {
            strcpy (arg_own_buf, "E00");
            return;
         }
         if (VG_(fstat) (fd, &stat_doc) != 0) {
            VG_(close) (fd);
            strcpy (arg_own_buf, "E00");
            return;
         }
         doc_len = stat_doc.size;
         
         if (len > PBUFSIZ - POVERHSIZ)
            len = PBUFSIZ - POVERHSIZ;

         if (ofs > doc_len) {
            write_enn (arg_own_buf);
            VG_(close) (fd);
            return;
         }
         VG_(lseek) (fd, ofs, VKI_SEEK_SET);
         len_read = VG_(read) (fd, toread, len);
         *new_packet_len_p = write_qxfer_response (arg_own_buf, toread,
                                                   len_read, ofs + len_read < doc_len);
         VG_(close) (fd);
         return;
      }
   }

   /* Protocol features query.  */
   if (strncmp ("qSupported", arg_own_buf, 10) == 0
       && (arg_own_buf[10] == ':' || arg_own_buf[10] == '\0')) {
      VG_(sprintf) (arg_own_buf, "PacketSize=%x", PBUFSIZ - 1);
      /* Note: max packet size including frame and checksum, but without
         trailing null byte, which is not sent/received. */
      
      strcat (arg_own_buf, ";QStartNoAckMode+");
      strcat (arg_own_buf, ";QPassSignals+");

      if ((*the_target->target_xml)() != NULL
          || (*the_target->shadow_target_xml)() != NULL) {
         strcat (arg_own_buf, ";qXfer:features:read+");
         /* if a new gdb connects to us, we have to reset the register
            set to the normal register sets to allow this new gdb to
            decide to use or not the shadow registers.
            
            Note that the reset is only done for gdb that are sending
            qSupported packets. If a user first connected with a recent
            gdb using shadow registers and then with a very old gdb
            that does not use qSupported packet, then the old gdb will
            not properly connect. */
         initialize_shadow_low(False);
      }
      return;
   }

   /* Otherwise we didn't know what packet it was.  Say we didn't
      understand it.  */
   arg_own_buf[0] = 0;
}

/* Handle all of the extended 'v' packets.  */
static
void handle_v_requests (char *arg_own_buf, char *status, int *signal)
{
   /* vcont packet code from gdb 6.6 removed */

   /* Otherwise we didn't know what packet it was.  Say we didn't
      understand it.  */
   arg_own_buf[0] = 0;
   return;
}

static
void myresume (int step, int sig)
{
   struct thread_resume resume_info[2];
   int n = 0;

   if (step || sig || (cont_thread != 0 && cont_thread != -1)) {
      resume_info[0].thread
         = ((struct inferior_list_entry *) current_inferior)->id;
      resume_info[0].step = step;
      resume_info[0].sig = sig;
      resume_info[0].leave_stopped = 0;
      n++;
   }
   resume_info[n].thread = -1;
   resume_info[n].step = 0;
   resume_info[n].sig = 0;
   resume_info[n].leave_stopped = (cont_thread != 0 && cont_thread != -1);

   resume_packet_needed = True;
   (*the_target->resume) (resume_info);
}

/* server_main global variables */
static char *own_buf;
static unsigned char *mem_buf;

void gdbserver_init (void)
{
   dlog(1, "gdbserver_init gdbserver embedded in valgrind: %s\n", version);
   noack_mode = False;
   initialize_low ();
   own_buf = malloc (PBUFSIZ);
   mem_buf = malloc (PBUFSIZ);
}

void gdbserver_terminate (void)
{
   /* last call to gdbserver is cleanup call */
   if (VG_MINIMAL_SETJMP(toplevel)) {
      dlog(0, "error caused VG_MINIMAL_LONGJMP to gdbserver_terminate\n");
      return;
   }
   remote_close();
}

void server_main (void)
{
   static char status;
   static int signal;

   char ch;
   int i = 0;
   unsigned int len;
   CORE_ADDR mem_addr;

   signal = mywait (&status);
   if (VG_MINIMAL_SETJMP(toplevel)) {
      dlog(0, "error caused VG_MINIMAL_LONGJMP to server_main\n");
   }
   while (1) {
      unsigned char sig;
      int packet_len;
      int new_packet_len = -1;
      
      if (resume_packet_needed) {
         resume_packet_needed = False;
         prepare_resume_reply (own_buf, status, signal);
         putpkt (own_buf);
      }

      packet_len = getpkt (own_buf);
      if (packet_len <= 0)
         break;

      i = 0;
      ch = own_buf[i++];
      switch (ch) {
      case 'Q':
         handle_set (own_buf, &new_packet_len);
         break;
      case 'q':
         handle_query (own_buf, &new_packet_len);
         break;
      case 'd':
         /* set/unset debugging is done through valgrind debug level. */
         own_buf[0] = '\0';
         break;
      case 'D':
         reset_valgrind_sink("gdb detaching from process");

         /* When detaching or kill the process, gdb expects to get
            an packet OK back.  Any other output will make gdb
            believes detach did not work. */
         write_ok (own_buf);
         putpkt (own_buf);
         remote_finish (reset_after_error);
         remote_open (VG_(clo_vgdb_prefix));
         myresume (0, 0);
         resume_packet_needed = False;
         return;
      case '!':
         /* We can not use the extended protocol with valgrind,
            because we can not restart the running
            program.  So return unrecognized.  */
         own_buf[0] = '\0';
         break;
      case '?':
         prepare_resume_reply (own_buf, status, signal);
         break;
      case 'H':
         if (own_buf[1] == 'c' || own_buf[1] == 'g' || own_buf[1] == 's') {
            unsigned long gdb_id, thread_id;
            
            gdb_id = strtoul (&own_buf[2], NULL, 16);
            thread_id = gdb_id_to_thread_id (gdb_id);
            if (thread_id == 0) {
               write_enn (own_buf);
               break;
            }

            if (own_buf[1] == 'g') {
               general_thread = thread_id;
               set_desired_inferior (1);
            } else if (own_buf[1] == 'c') {
               cont_thread = thread_id;
            } else if (own_buf[1] == 's') {
               step_thread = thread_id;
            }
            
            write_ok (own_buf);
         } else {
            /* Silently ignore it so that gdb can extend the protocol
               without compatibility headaches.  */
            own_buf[0] = '\0';
         }
         break;
      case 'g':
         set_desired_inferior (1);
         registers_to_string (own_buf);
         break;
      case 'G':
         set_desired_inferior (1);
         registers_from_string (&own_buf[1]);
         write_ok (own_buf);
         break;
      case 'P': {
         int regno;
         char *regbytes;
         Bool mod;
         ThreadState *tst;
         regno = strtol(&own_buf[1], NULL, 16);
         regbytes = strchr(&own_buf[0], '=') + 1;
         set_desired_inferior (1);
         tst = (ThreadState *) inferior_target_data (current_inferior);
         /* Only accept changing registers in "runnable state3.
            In fact, it would be ok to change most of the registers
            except a few "sensitive" registers such as the PC, SP, BP.
            We assume we do not need to very specific here, and that we
            can just refuse all of these. */
         if (tst->status == VgTs_Runnable || tst->status == VgTs_Yielding) {
            supply_register_from_string (regno, regbytes, &mod);
            write_ok (own_buf);
         } else {
            /* at least from gdb 6.6 onwards, an E. error
               reply is shown to the user. So, we do an error
               msg which both is accepted by gdb as an error msg
               and is readable by the user. */
            VG_(sprintf) 
               (own_buf,
"E.\n"
"ERROR changing register %s regno %d\n"
"gdb commands changing registers (pc, sp, ...) (e.g. 'jump',\n"
"set pc, calling from gdb a function in the debugged process, ...)\n"
"can only be accepted if the thread is VgTs_Runnable or VgTs_Yielding state\n"
"Thread status is %s\n",
                find_register_by_number (regno)->name, regno,
                VG_(name_of_ThreadStatus)(tst->status));
            if (VG_(clo_verbosity) > 1)
               VG_(umsg) ("%s\n", own_buf);
         }
         break;            
      }
      case 'm':
         decode_m_packet (&own_buf[1], &mem_addr, &len);
         if (read_inferior_memory (mem_addr, mem_buf, len) == 0)
            convert_int_to_ascii (mem_buf, own_buf, len);
         else
            write_enn (own_buf);
         break;
      case 'M':
         decode_M_packet (&own_buf[1], &mem_addr, &len, mem_buf);
         if (write_inferior_memory (mem_addr, mem_buf, len) == 0)
            write_ok (own_buf);
         else
            write_enn (own_buf);
         break;
      case 'X':
         if (decode_X_packet (&own_buf[1], packet_len - 1,
                              &mem_addr, &len, mem_buf) < 0
             || write_inferior_memory (mem_addr, mem_buf, len) != 0)
            write_enn (own_buf);
         else
            write_ok (own_buf);
         break;
      case 'C':
         convert_ascii_to_int (own_buf + 1, &sig, 1);
         if (target_signal_to_host_p (sig))
            signal = target_signal_to_host (sig);
         else
            signal = 0;
         set_desired_inferior (0);
         myresume (0, signal);
         return; // return control to valgrind
      case 'S':
         convert_ascii_to_int (own_buf + 1, &sig, 1);
         if (target_signal_to_host_p (sig))
            signal = target_signal_to_host (sig);
         else
            signal = 0;
         set_desired_inferior (0);
         myresume (1, signal);
         return; // return control to valgrind
      case 'c':
         set_desired_inferior (0);
         myresume (0, 0);
         return; // return control to valgrind
      case 's':
         set_desired_inferior (0);
         myresume (1, 0);
         return; // return control to valgrind
      case 'Z': {
         char *lenptr;
         char *dataptr;
         CORE_ADDR addr = strtoul (&own_buf[3], &lenptr, 16);
         int zlen = strtol (lenptr + 1, &dataptr, 16);
         char type = own_buf[1];
         
         if (the_target->insert_watchpoint == NULL
             || (type < '0' || type > '4')) {
            /* No watchpoint support or not a watchpoint command;
               unrecognized either way.  */
            own_buf[0] = '\0';
         } else {
            int res;
            
            res = (*the_target->insert_watchpoint) (type, addr, zlen);
            if (res == 0)
               write_ok (own_buf);
            else if (res == 1)
               /* Unsupported.  */
               own_buf[0] = '\0';
            else
               write_enn (own_buf);
         }
         break;
      }
      case 'z': {
         char *lenptr;
         char *dataptr;
         CORE_ADDR addr = strtoul (&own_buf[3], &lenptr, 16);
         int zlen = strtol (lenptr + 1, &dataptr, 16);
         char type = own_buf[1];
         
         if (the_target->remove_watchpoint == NULL
             || (type < '0' || type > '4')) {
            /* No watchpoint support or not a watchpoint command;
               unrecognized either way.  */
            own_buf[0] = '\0';
         } else {
            int res;
            
            res = (*the_target->remove_watchpoint) (type, addr, zlen);
            if (res == 0)
               write_ok (own_buf);
            else if (res == 1)
               /* Unsupported.  */
               own_buf[0] = '\0';
            else
               write_enn (own_buf);
         }
         break;
      }
      case 'k':
         kill_request("Gdb request to kill this process\n");
         break;
      case 'T': {
         unsigned long gdb_id, thread_id;
         
         gdb_id = strtoul (&own_buf[1], NULL, 16);
         thread_id = gdb_id_to_thread_id (gdb_id);
         if (thread_id == 0) {
            write_enn (own_buf);
            break;
         }

         if (mythread_alive (thread_id))
            write_ok (own_buf);
         else
            write_enn (own_buf);
         break;
      }
      case 'R':
         /* Restarting the inferior is only supported in the
            extended protocol.
            => It is a request we don't understand.  Respond with an
            empty packet so that gdb knows that we don't support this
            request.  */
         own_buf[0] = '\0';
         break;
      case 'v':
         /* Extended (long) request.  */
         handle_v_requests (own_buf, &status, &signal);
         break;
      default:
         /* It is a request we don't understand.  Respond with an
            empty packet so that gdb knows that we don't support this
            request.  */
         own_buf[0] = '\0';
         break;
      }

      if (new_packet_len != -1)
         putpkt_binary (own_buf, new_packet_len);
      else
         putpkt (own_buf);
      
      if (status == 'W')
         VG_(umsg) ("\nChild exited with status %d\n", signal);
      if (status == 'X')
         VG_(umsg) ("\nChild terminated with signal = 0x%x (%s)\n",
                    target_signal_to_host (signal),
                    target_signal_to_name (signal));
      if (status == 'W' || status == 'X') {
         VG_(umsg) ("Process exiting\n");
         VG_(exit) (0);
      }
   }

   /* We come here when getpkt fails => close the connection,
      and re-open. Then return control to valgrind.
      We return the control to valgrind as we assume that
      the connection was closed due to vgdb having finished
      to execute a command. */
   if (VG_(clo_verbosity) > 1)
      VG_(umsg) ("Remote side has terminated connection.  "
                 "GDBserver will reopen the connection.\n");
   remote_finish (reset_after_error);
   remote_open (VG_(clo_vgdb_prefix)); 
   myresume (0, 0);
   resume_packet_needed = False;
   return;
}
