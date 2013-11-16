#include <stdio.h>
#include <stdint.h>

#include "stranslate.h"

/*
 * types
 */

typedef struct
{
    uint32_t    uint32;
} subtype_t;

typedef struct
{
    uint8_t     uint8;
    uint16_t    uint16;
    uint32_t    uint32;
    subtype_t   subtype;
    uint16_t    arr[4];
    uint32_t    uint32_2;
} foo_t;

/*
 * const data
 */

type_map_t subtype_map[] =
    {
    strans_primitive( subtype_t, uint32 )
    };

type_map_t foo_map[] = 
    {
    strans_primitive( foo_t, uint8 ),
    strans_primitive( foo_t, uint16 ),
    strans_primitive( foo_t, uint32 ),
    strans_struct( foo_t, subtype, subtype_map, array_cnt(subtype_map) ),
    strans_primitive_array( foo_t, arr, 4 ),
    strans_primitive( foo_t, uint32_2 )
    };

static const foo_t foo_init_data =
{
    117,
    12345,
    97293122,
    { 24579234 },
    { 3812, 16231, 114, 33333 },
    8394023
};

/*
 * prototypes
 */


/*
 * functions
 */

int main( int argc, char * argv[] )
{
    foo_t foo;

    foo = foo_init_data;

    printf("BEFORE:\n");
    strans_print_by_map( &foo, foo_map, array_cnt(foo_map) );
    putchar( '\n' );

    strans_reverse_bytes_by_map( &foo, foo_map, array_cnt(foo_map) );

    printf("AFTER:\n");
    strans_print_by_map( &foo, foo_map, array_cnt(foo_map) );

    return( 0 );
}
