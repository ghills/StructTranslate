//
//  stranslate.c
//  
//
//  Created by Gavin Hills on 11/15/13.
//
//

#include <assert.h>
#include <stdint.h>

#include "stranslate.h"

void strans_reverse_bytes
    (
    uint8_t * data,
    uint8_t   cnt
    )
{
#define swap( a, b, t ) { t = a; a = b; b = t; }

uint8_t temp;
uint8_t i;

assert( cnt > 0 );

for( i = 0; i < ( cnt / 2 ); i++ )
    {
    swap( data[i], data[cnt-1-i], temp );
    }
    
#undef swap
}

void strans_reverse_bytes_by_map
    (
    void       * data,
    type_map_t * map,
    uint16_t     map_count
    )
{
uint16_t i;
uint16_t j;

assert( map_count > 0 );

for( i = 0; i < map_count; i++ )
    {
    assert( map[i].elem_count > 0 );
    
    // if the element is size 1, no need to do anything
    if( map[i].elem_size == 1 )
        {
        continue;
        }
    
    for( j = 0; j < map[i].elem_count; j++ )
        {
        if( map[i].type_map )
            {
            // nested structure, recurse!
            //TODO: max depth limit this
            strans_reverse_bytes_by_map( (void *)( data + map[i].offset + (j * map[i].elem_size)), map[i].type_map, map[i].type_count );
            }
        else
            {
            // this field must be reversable
            strans_reverse_bytes( (void *)( data + map[i].offset + (j * map[i].elem_size)), map[i].elem_size );
            }
        }
    }
}