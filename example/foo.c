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

/*
 * prototypes
 */

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
 * functions
 */


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

void print_foo_type( foo_t * str )
{
    uint16_t i;
    uint8_t * ptr;

    ptr = (uint8_t *)str;

    for( i = 0; i < array_cnt(foo_map); i++ )
        {
        if( foo_map[i].elem_count > 1 )
            {
            print_n_elements( &ptr[ foo_map[i].offset ], foo_map[i].elem_count, foo_map[i].elem_size ); 
            }
        else
            {
            print_n_bytes( &ptr[ foo_map[i].offset ], foo_map[i].elem_size ); 
            }
        putchar('\n');
        }
}

int main( int argc, char * argv[] )
{
    foo_t foo;

    foo.uint8 = 117;
    foo.uint16 = 12345;
    foo.uint32 = 97293122;
    foo.subtype.uint32 = 24579234;
    foo.arr[0] = 3812;
    foo.arr[1] = 16231;
    foo.arr[2] = 114;
    foo.arr[3] = 33333;
    foo.uint32_2 = 8394023;

    printf("BEFORE:\n");
    print_foo_type( &foo );
    putchar( '\n' );

    strans_reverse_bytes_by_map( &foo, foo_map, array_cnt(foo_map) );

    printf("AFTER:\n");
    print_foo_type( &foo );

    return( 0 );
}
