
/*--------------------------------------------------------------------*/
/*--- Nulgrind: The minimal Valgrind tool.               mm_main.c ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of Nulgrind, the minimal Valgrind tool,
   which does no instrumentation or analysis.

   Copyright (C) 2002-2010 Nicholas Nethercote
      njn@valgrind.org

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
#include "pub_tool_tooliface.h"

//------------------------------------------------------------//
//--- malloc() et al replacement wrappers                  ---//
//------------------------------------------------------------//

//static void* dh_malloc ( ThreadId tid, SizeT szB )
//{
//	return new_block( tid, NULL, szB, VG_(clo_alignment), /*is_zeroed*/False );
//}

//static void* dh___builtin_new ( ThreadId tid, SizeT szB )
//{
//	return new_block( tid, NULL, szB, VG_(clo_alignment), /*is_zeroed*/False );
//}

//static void* dh___builtin_vec_new ( ThreadId tid, SizeT szB )
//{
//	return new_block( tid, NULL, szB, VG_(clo_alignment), /*is_zeroed*/False );
//}

//static void* dh_calloc ( ThreadId tid, SizeT m, SizeT szB )
//{
//	return new_block( tid, NULL, m*szB, VG_(clo_alignment), /*is_zeroed*/True );
//}

//static void *dh_memalign ( ThreadId tid, SizeT alignB, SizeT szB )
//{
//	return new_block( tid, NULL, szB, alignB, False );
//}

//static void dh_free ( ThreadId tid __attribute__((unused)), void* p )
//{
//	die_block( p, /*custom_free*/False );
//}

//static void dh___builtin_delete ( ThreadId tid, void* p )
//{
//	die_block( p, /*custom_free*/False);
//}

//static void dh___builtin_vec_delete ( ThreadId tid, void* p )
//{
//	die_block( p, /*custom_free*/False );
//}

//static void* dh_realloc ( ThreadId tid, void* p_old, SizeT new_szB )
//{
//	if (p_old == NULL) {
//		return dh_malloc(tid, new_szB);
//	}
//	if (new_szB == 0) {
//		dh_free(tid, p_old);
//		return NULL;
//	}
//	return renew_block(tid, p_old, new_szB);
//}

//static SizeT dh_malloc_usable_size ( ThreadId tid, void* p )
//{
//	tl_assert(0);
//	//zz   HP_Chunk* hc = VG_(HT_lookup)( malloc_list, (UWord)p );
//	//zz
//	//zz   return ( hc ? hc->req_szB + hc->slop_szB : 0 );
//}

//------------------------------------------------------------//
//--- Initialization stuff								   ---//
//------------------------------------------------------------//


static void mm_post_clo_init(void)
{
	
}

static
IRSB* mm_instrument ( VgCallbackClosure* closure,
                      IRSB* bb,
                      VexGuestLayout* layout, 
                      VexGuestExtents* vge,
                      IRType gWordTy, IRType hWordTy )
{
    return bb;
}

static
void mm_mem_mmap ( Addr a, SizeT len,
					  Bool rr, Bool ww, Bool xx, ULong di_handle )
{
	VG_(printf)("[0x%x]: %d\n",a,len);
}

static void mm_fini(Int exitcode)
{
}

static void mm_pre_clo_init(void)
{
   VG_(details_name)            ("Memmap");
   VG_(details_version)         (NULL);
   VG_(details_description)     ("the memory mapper");
   VG_(details_copyright_author)("Copyright something something.");
   VG_(details_bug_reports_to)  (VG_BUGS_TO);

   VG_(basic_tool_funcs)        (mm_post_clo_init,
                                 mm_instrument,
                                 mm_fini);
	VG_(track_new_mem_mmap)    ( mm_mem_mmap    );

//   VG_(needs_malloc_replacement)  (dh_malloc,
//                                   dh___builtin_new,
//                                   dh___builtin_vec_new,
//                                   dh_memalign,
//                                   dh_calloc,
//                                   dh_free,
//                                   dh___builtin_delete,
//                                   dh___builtin_vec_delete,
//                                   dh_realloc,
//                                   dh_malloc_usable_size,
//                                   0 );

	
   /* No needs, no core events to track */
}

VG_DETERMINE_INTERFACE_VERSION(mm_pre_clo_init)

/*--------------------------------------------------------------------*/
/*--- end                                                          ---*/
/*--------------------------------------------------------------------*/
