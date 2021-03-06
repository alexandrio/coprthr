/* event.h
 *
 * Copyright (c) 2009-2013 Brown Deer Technology, LLC.  All Rights Reserved.
 *
 * This software was developed by Brown Deer Technology, LLC.
 * For more information contact info@browndeertechnology.com
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3 (LGPLv3)
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* DAR */

#ifndef _event_h
#define _event_h

#include "printcl.h"
#include "coprthr_sched.h"
#include "coprthr_mem.h"
#include "coprthr_program.h"



/*
 * lock and sig
 */

#define __lock_event(ev) do { \
	printcl( CL_DEBUG "__lock_event: attempt %p",ev); \
	pthread_mutex_lock(&(ev->ev1->mtx)); \
	printcl( CL_DEBUG "__lock_event: locked %p",ev); \
	} while(0)

#define __unlock_event(ev) do { \
	pthread_mutex_unlock(&(ev->ev1->mtx)); \
	printcl( CL_DEBUG "__unlock_event: unlocked %p",ev); \
	} while(0)

#define __wait_event(ev) do { \
	printcl( CL_DEBUG "__wait_event: sleep%p",ev); \
	pthread_cond_wait(&(ev->ev1->sig),&(ev->ev1->mtx)); \
	printcl( CL_DEBUG "__wait_event: wake%p",ev); \
	} while(0)

#define __sig_event(ev) do { \
	printcl( CL_DEBUG "__sig_event: %p",ev); \
	pthread_cond_signal(&(ev->ev1->sig)); \
	} while(0)


#define __lock_event1(ev1) do { \
	printcl( CL_DEBUG "__lock_event1: attempt %p",ev1); \
	pthread_mutex_lock(&(ev1->mtx)); \
	printcl( CL_DEBUG "__lock_event1: locked %p",ev1); \
	} while(0)

#define __unlock_event1(ev1) do { \
	printcl( CL_DEBUG "__unlock_event1: attempt unlock %p",ev1); \
	pthread_mutex_unlock(&(ev1->mtx)); \
	printcl( CL_DEBUG "__unlock_event1: unlocked %p",ev1); \
	} while(0)

#define __wait_event1(ev1) do { \
	printcl( CL_DEBUG "__wait_event1: sleep%p",ev1); \
	pthread_cond_wait(&(ev1->sig),&(ev1->mtx)); \
	printcl( CL_DEBUG "__wait_event1: wake%p",ev1); \
	} while(0)

#define __sig_event1(ev1) do { \
	printcl( CL_DEBUG "__sig_event1: attempt signal %p",ev1); \
	pthread_cond_signal(&(ev1->sig)); \
	printcl( CL_DEBUG "__sig_event1: signaled %p",ev1); \
	} while(0)



void __do_release_event_1(struct coprthr_event* ev1) ;

void __do_set_cmd_read_buffer_1( struct coprthr_event* ev1, 
	struct coprthr_mem* src1, size_t src_offset, size_t len, void* dst);

void __do_set_cmd_write_buffer_1( struct coprthr_event* ev1, 
	struct coprthr_mem* dst1, size_t dst_offset, size_t len, const void* src);

void __do_set_cmd_copy_buffer_1( struct coprthr_event* ev1, 
	struct coprthr_mem* src1, struct coprthr_mem* dst1, size_t src_offset, 
	size_t dst_offset, size_t len );


void __do_set_cmd_read_image_1( struct coprthr_event* ev1, 
	struct coprthr_mem* src1, const size_t* src_origin, const size_t* region, 
	size_t row_pitch, size_t slice_pitch, void* dst);

void __do_set_cmd_write_image_1( struct coprthr_event* ev1, 
	struct coprthr_mem* dst1, const size_t* dst_origin, const size_t* region, 
	size_t row_pitch, size_t slice_pitch, const void* src);

void __do_set_cmd_copy_image_1( struct coprthr_event* ev1, 
	struct coprthr_mem* src1, struct coprthr_mem* dst1, 
	const size_t* src_origin, const size_t* dst_origin, const size_t* region);

void __do_set_cmd_copy_image_to_buffer_1( struct coprthr_event* ev1, 
	struct coprthr_mem* src1, struct coprthr_mem* dst1, 
	const size_t* src_origin, const size_t* region, size_t dst_offset);

void __do_set_cmd_copy_buffer_to_image_1( struct coprthr_event* ev1, 
	struct coprthr_mem* src1, struct coprthr_mem* dst1, size_t src_offset, 
	const size_t* dst_origin, const size_t* region);

void __do_set_cmd_map_buffer_1( struct coprthr_event* ev1, 
	struct coprthr_mem* membuf1, int flags, size_t offset, size_t len,
	void* pp);

void __do_set_cmd_map_image_1( struct coprthr_event* ev1, 
	struct coprthr_mem* image1, int flags, const size_t* origin, 
	const size_t* region, size_t* row_pitch, size_t* slice_pitch, void* p);

void __do_set_cmd_unmap_memobj_1( struct coprthr_event* ev1, 
	struct coprthr_mem* memobj1, void* p);

void __do_set_cmd_ndrange_kernel_1( struct coprthr_event* ev1,
	struct coprthr_kernel* krn1, unsigned int work_dim, 
	const size_t* global_work_offset, const size_t* global_work_size,
	const size_t* local_work_size);

void __do_set_cmd_ndrange_kernel_n( struct coprthr_event* ev1,
	unsigned int nkrn,
	struct coprthr_kernel* v_krn1[], unsigned int v_work_dim[], 
	size_t* v_global_work_offset[], size_t* v_global_work_size[],
	size_t* v_local_work_size[]);

void __do_set_cmd_task_1( struct coprthr_event* ev1, 
	struct coprthr_kernel* krn1);

void __do_wait_1( struct coprthr_event* ev1 );

#endif

