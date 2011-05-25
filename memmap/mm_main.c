
/*--------------------------------------------------------------------*/
/*--- Memmap: The dynamic memory tracer tool.            mm_main.c ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of Nulgrind, the minimal Valgrind tool,
   which does no instrumentation or analysis.

   Copyright (C) 2011 stuff

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#include "pub_tool_basics.h"
#include "pub_tool_libcbase.h"
#include "pub_tool_libcassert.h"
#include "pub_tool_libcprint.h"
#include "pub_tool_machine.h"      // VG_(fnptr_to_fnentry)
#include "pub_tool_mallocfree.h"
#include "pub_tool_options.h"
#include "pub_tool_replacemalloc.h"
#include "pub_tool_tooliface.h"
#include "pub_tool_wordfm.h"

int mm_mallocs = 0;

//------------------------------------------------------------//
//--- Heap management                                      ---//
//------------------------------------------------------------//



//------------------------------------------------------------//
//--- malloc() et al replacement wrappers                  ---//
//------------------------------------------------------------//

static void* mm_malloc ( ThreadId tid, SizeT szB )
{
    VG_(printf)("Malloc'd stuff.\n");
    mm_mallocs++;
    return 0; //return alloc_and_record_block( tid, szB, VG_(clo_alignment), /*is_zeroed*/False );
}

///////////////// Begin instrumenting stuff //////////////////////

static void mm_mem_mmap ( Addr a, SizeT len, Bool rr, Bool ww, Bool xx, ULong di_handle )
{
    VG_(printf)("Mmap: [%p]: %llu\n",a,len);
}

static void mm_mem_munmap ( Addr a, SizeT len)
{
    VG_(printf)("[0x%x]: %d unmapped\n",a,len);
}

static void mm_new_mem_startup( Addr a, SizeT len,
                                 Bool rr, Bool ww, Bool xx, ULong di_handle )
{
    VG_(printf)("MemStartup: [%p]: %llu\n",a,len);
}

static void mm_post_write (ThreadId tid, PtrdiffT guest_state_offset, SizeT size, Addr f)
{
    VG_(printf)("mm_post_write\n");
}

static void mm_die_mem_munmap ( Addr a, SizeT len )
{
    VG_(printf)("Free: [%p]: %llu\n",a,len);
}


///////////////// End instrumenting stuff ////////////////////////


static void* new_block ( ThreadId tid, void* p, SizeT req_szB, SizeT req_alignB, Bool is_zeroed )
{
    tl_assert(p == NULL); // don't handle custom allocators right now
    SizeT actual_szB, slop_szB;

    if ((SSizeT)req_szB < 0) return NULL;

    if (req_szB == 0)
        req_szB = 1;  /* can't allow zero-sized blocks in the interval tree */

    // Allocate and zero if necessary
    if (!p) {
        p = VG_(cli_malloc)( req_alignB, req_szB );
        if (!p) {
            return NULL;
        }
        if (is_zeroed) VG_(memset)(p, 0, req_szB);
        actual_szB = VG_(malloc_usable_size)(p);
        tl_assert(actual_szB >= req_szB);
        slop_szB = actual_szB - req_szB;
    } else {
        slop_szB = 0;
    }

    return p;
}


//------------------------------------------------------------//
//--- malloc() et al replacement wrappers                  ---//
//------------------------------------------------------------//

static void *mm_malloc ( ThreadId tid, SizeT szB )
{
    VG_(printf)("Allocating %u bytes.",szB);
    return new_block( tid, NULL, szB, VG_(clo_alignment), /*is_zeroed*/False );
}

static void *mm___builtin_new ( ThreadId tid, SizeT szB )
{
    VG_(printf)("Allocating new %u bytes.",szB);
	return new_block( tid, NULL, szB, VG_(clo_alignment), /*is_zeroed*/False );
}

static void *mm___builtin_vec_new ( ThreadId tid, SizeT szB )
{
	return new_block( tid, NULL, szB, VG_(clo_alignment), /*is_zeroed*/False );
}

static void *mm_calloc ( ThreadId tid, SizeT m, SizeT szB )
{
	return new_block( tid, NULL, m*szB, VG_(clo_alignment), /*is_zeroed*/True );
}

static void *mm_memalign ( ThreadId tid, SizeT alignB, SizeT szB )
{
	return new_block( tid, NULL, szB, alignB, False );
}

static void *mm_free ( ThreadId tid __attribute__((unused)), void* p )
{
    VG_(printf)("Freeing.\n");
	VG_(cli_free)( p );
}

static void *mm___builtin_delete ( ThreadId tid, void* p )
{
	VG_(printf)("Deleting.\n");
	VG_(cli_free)( p );
}

static void *mm___builtin_vec_delete ( ThreadId tid, void* p )
{
	VG_(printf)("VecDeleting.\n");
	VG_(cli_free)( p );
}

static void *mm_realloc ( ThreadId tid, void* p_old, SizeT new_szB )
{
	
	if (p_old == NULL) {
		return mm_malloc(tid, new_szB);
	}
	if (new_szB == 0) {
		mm_free(tid, p_old);
		return NULL;
	}
	return mm_malloc(tid, new_szB);
}

static SizeT mm_malloc_usable_size ( ThreadId tid, void* p )
{                                                            
    return 0;
}                                                            

////////////////// End malloc replacements ////////////////////

static void mm_post_clo_init(void)
{
    VG_(printf)("mm_post_clo_init\n");
}

static IRSB* mm_instrument ( VgCallbackClosure* closure,
                             IRSB* bb,
                             VexGuestLayout* layout,
                             VexGuestExtents* vge,
                             IRType gWordTy, IRType hWordTy )
{

    return bb;
}

static void mm_fini(Int exitcode)
{
    VG_(printf)("mm_fini\n");
    VG_(printf)("mallocs: %d\n", mm_mallocs);
}

static void mm_pre_clo_init(void)
{
    VG_(printf)("mm_pre_clo_init\n");

    VG_(details_name)            ("Memmap");
    VG_(details_version)         (NULL);
    VG_(details_description)     ("the memory mapper");
    VG_(details_copyright_author)("Copyright 2011 something something.");
    VG_(details_bug_reports_to)  (VG_BUGS_TO);

    VG_(basic_tool_funcs)        (mm_post_clo_init,
                                  mm_instrument,
                                  mm_fini);
    //VG_(needs_libc_freeres)();
    //VG_(needs_client_requests)     (ms_handle_client_request);


//    VG_(track_new_mem_mmap)      (mm_mem_mmap);
//    VG_(track_new_mem_startup)   (mm_new_mem_startup);
//    VG_(track_die_mem_munmap)    (mm_die_mem_munmap );

    VG_(basic_tool_funcs)        (mm_post_clo_init,
                                  mm_instrument,
                                  mm_fini);

    VG_(track_new_mem_mmap)      (mm_mem_mmap);
    VG_(track_die_mem_munmap)    (mm_mem_munmap);

    VG_(track_post_reg_write_clientcall_return) (mm_post_write);

    VG_(needs_malloc_replacement)  (mm_malloc,
                                    mm___builtin_new,
                                    mm___builtin_vec_new,
                                    mm_memalign,
                                    mm_calloc,
                                    mm_free,
                                    mm___builtin_delete,
                                    mm___builtin_vec_delete,
                                    mm_realloc,
                                    mm_malloc_usable_size,
                                    0 );


}

VG_DETERMINE_INTERFACE_VERSION(mm_pre_clo_init)

        /*--------------------------------------------------------------------*/
        /*--- end                                                          ---*/
        /*--------------------------------------------------------------------*/
