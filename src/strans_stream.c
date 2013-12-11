/*
 *  strans_stream.c
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
 
static void stream_collapse
    (
    void const * const
                data,
    type_map_t const * const
                map,
    uint16_t    map_count,
    uint8_t   * buf,
    uint16_t    buf_sz,
    uint8_t     iters_remain
    );
    
static void stream_expand
    (
    void const * const
                data,
    type_map_t const * const
                map,
    uint16_t    map_count,
    uint8_t   * buf,
    uint16_t    buf_sz,
    uint8_t     iters_remain
    );

/* 
 * Private Functions
 */

static void stream_collapse
    (
    void const * const
                data,
    type_map_t const * const
                map,
    uint16_t    map_count,
    uint8_t   * buf,
    uint16_t    buf_sz,
    uint8_t     iters_remain
    )
{
/* TODO: implement */
}

static void stream_expand
    (
    void const * const
                data,
    type_map_t const * const
                map,
    uint16_t    map_count,
    uint8_t   * buf,
    uint16_t    buf_sz,
    uint8_t     iters_remain
    )
{
/* TODO: implement */
}

/*
 * Public Functions
 */

void strans_stream_collapse
    (
    void const * const
                data,
    type_map_t const * const
                map,
    uint16_t    map_count,
    uint8_t   * buf,
    uint16_t    buf_sz
    )
{
stream_collapse( data, map, map_count, buf, buf_sz, MAX_RECURSION_DEPTH );
}

void strans_stream_expand
    (
    void const * const
                data,
    type_map_t const * const
                map,
    uint16_t    map_count,
    uint8_t   * buf,
    uint16_t    buf_sz
    )
{
stream_expand( data, map, map_count, buf, buf_sz, MAX_RECURSION_DEPTH );
}
