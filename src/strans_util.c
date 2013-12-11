/*
 *  strans_util.c
 *  
 *
 *  Created by Gavin Hills on 12/10/13.
 *
 */
 
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
/* TODO: implement */

return( 0 );
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
