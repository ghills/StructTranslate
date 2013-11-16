/*
 *  strans_print.c
 *  
 *
 *  Created by Gavin Hills on 11/15/13.
 *
 */

#include <stdio.h>

#include "stranslate.h"

/*
 * defines
 */

#define MAX_PRINT_DEPTH ( 10 )

/*
 * declarations
 */

static void print_by_map
    (
    void const * const 
                 data,
    type_map_t const * const
                 map,
    uint16_t     map_count,
    uint8_t      iter_depth
    );

static void print_n_bytes
    ( 
    uint8_t const * const 
                data,
    uint16_t    cnt
    );

static void print_n_elements
    (
    uint8_t const * const 
                data,
    uint16_t    cnt,
    uint16_t    elem_sz
    );

/* 
 * Private Functions
 */


static void print_by_map
    (
    void const * const 
                 data,
    type_map_t const * const
                 map,
    uint16_t     map_count,
    uint8_t      iter_depth
    )
{
uint16_t i;
uint16_t j;
uint8_t * ptr;
uint8_t tab_i;

ptr = (uint8_t *)data;

for( i = 0; i < map_count; i++ )
    {
    /* indent in the right number of tabs */
    for( tab_i = 0; tab_i < iter_depth; tab_i++ )
        {
        putchar('\t');
        }

    if( map[i].type_map )
        {
        for( j = 0; j < map[i].elem_count; j++ )
            {
            putchar('{');
            putchar('\n');
            /* print sub structure */
            if( iter_depth < MAX_PRINT_DEPTH )
                {
                print_by_map( &ptr[map[i].offset] + (j*map[i].elem_size), map[i].type_map, map[i].type_count, iter_depth + 1 );
                }
            else
                {   
                printf("MAX DEPTH REACHED\n");
                }
            putchar('}');
            }
        }
    else
        {
        /* print primitive */
        print_n_elements( &ptr[ map[i].offset ], map[i].elem_count, map[i].elem_size ); 
        }
    putchar('\n');
    }
}


static void print_n_bytes
    ( 
    uint8_t const * const 
                data,
    uint16_t    cnt
    )
{
uint16_t i;

for( i = 0; i < cnt; i++ )
    {
    printf( "%02X ", data[i] );
    }

}


static void print_n_elements
    (
    uint8_t const * const 
                data,
    uint16_t    cnt,
    uint16_t    elem_sz
    )
{
uint16_t i;

for( i = 0; i < cnt; i++ )
    {
    putchar('[');
    putchar(' ');
    print_n_bytes( data + ( elem_sz * i ), elem_sz );
    putchar(']');
    }

}


/* 
 * Public Functions
 */

void strans_print_by_map
    (
    void const * const 
                 data,
    type_map_t const * const
                 map,
    uint16_t     map_count
    )
{
print_by_map( data, map, map_count, 0 );
}
