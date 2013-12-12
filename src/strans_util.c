/*
 *  strans_util.c
 *  
 *
 *  Created by Gavin Hills on 12/10/13.
 *
 */
 
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
 
static uint32_t map_data_size
    (
    type_map_t const * const
                map,
    uint16_t    map_count,
    uint8_t     iters_remain
    );
    
/* 
 * Private Functions
 */

static uint32_t map_data_size
    (
    type_map_t const * const
                map,
    uint16_t    map_count,
    uint8_t     iters_remain
    )
{
uint32_t size;
uint16_t i;

size = 0;

for( i = 0; i < map_count; i++ )
    {
    if( map[i].type_map )
        {
        /* nested structure, recurse! */
        if( iters_remain > 0 )
            {
            size += ( map[i].elem_count * map_data_size( map[i].type_map, map[i].type_count, iters_remain - 1 ) );
            }
        else
            {
            perror("Recursion Depth");
            exit(-1);
            }
        }
    else
        {
        /* copy this amount */
        size += ( map[i].elem_count * map[i].elem_size );
        }
    }

return( size );

}

/*
 * Public Functions
 */

uint32_t strans_map_data_size
    (
    type_map_t const * const
                map,
    uint16_t    map_count
    )
{
return( map_data_size( map, map_count, MAX_RECURSION_DEPTH ) );
}
