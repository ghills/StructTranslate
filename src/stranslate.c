/*
 *  stranslate.c
 *  
 *
 *  Created by Gavin Hills on 11/15/13.
 *
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "stranslate.h"

/*
 * defines
 */

#define MAX_RECURSION_DEPTH ( 255 )

/*
 * declarations
 */

static void reverse_bytes_by_map
    (
    void * const data,
    type_map_t const * const 
                 map,
    uint16_t     map_count,
    uint8_t      iters_remain
    );

/* 
 * Private Functions
 */

static void reverse_bytes_by_map
    (
    void * const data,
    type_map_t const * const 
                 map,
    uint16_t     map_count,
    uint8_t      iters_remain
    )
{
uint16_t i;
uint16_t j;

assert( map_count > 0 );

for( i = 0; i < map_count; i++ )
    {
    assert( map[i].elem_count > 0 );
    
    /* if the element is size 1, no need to do anything */
    if( map[i].elem_size == 1 )
        {
        continue;
        }
    
    for( j = 0; j < map[i].elem_count; j++ )
        {
        if( map[i].type_map )
            {
            /* nested structure, recurse! */
            if( iters_remain > 0 )
                {
                reverse_bytes_by_map( (void *)( (uint8_t *)data + map[i].offset + (j * map[i].elem_size)), map[i].type_map, map[i].type_count, iters_remain - 1 );
                }
            else
                {
                perror("Recursion Depth");
                exit(-1);
                }
            }
        else
            {
            /* this field must be reversable */
            strans_reverse_bytes( (void *)( (uint8_t *)data + map[i].offset + (j * map[i].elem_size)), map[i].elem_size );
            }
        }
    }
}

/*
 * Public Functions
 */

void strans_reverse_bytes
    (
    uint8_t * const data,
    uint8_t         cnt
    )
{
#define swap( a, b ) {uint8_t _t; _t = a; a = b; b = _t; }

uint8_t i;

assert( cnt > 0 );

for( i = 0; i < ( cnt / 2 ); i++ )
    {
    swap( data[i], data[cnt-1-i] );
    }
    
#undef swap
}

void strans_reverse_bytes_by_map
    (
    void * const data,
    type_map_t const * const 
                 map,
    uint16_t     map_count
    )
{
reverse_bytes_by_map( data, map, map_count, MAX_RECURSION_DEPTH );
}

