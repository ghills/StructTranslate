//
//  stranslate.h
//  
//
//  Created by Gavin Hills on 11/15/13.
//
//

#ifndef _stranslate_h
#define _stranslate_h


/*
 * Includes
 */

#include <stdint.h>


/*
 *  Macros
 */

#ifndef cnt_of_array
#define cnt_of_array( arr ) ( sizeof(arr) / sizeof(arr[0]) )
#endif

#ifndef offsetof
#define offsetof( t, f ) ( (uint16_t)(&(((t *)0)->f)) )
#endif

#ifndef sizeof_field
#define sizeof_field( t, f ) sizeof( ( (t * )0 )->f )
#endif

#define strans_primitive_array( type, field, cnt ) \
    { ( sizeof_field( type, field ) / cnt ), cnt, offsetof( type, field ), NULL, 0 }

#define strans_primitive( type, field ) \
    strans_primitive_array( type, field, 1 )

#define strans_struct_array( type, field, cnt, map, map_cnt ) \
    { ( sizeof_field( type, field ) / cnt ), cnt, offsetof( type, field ), map, map_cnt }

#define strans_struct( type, field, map, map_cnt ) \
    strans_struct_array( type, field, 1, map, map_cnt )


/*
 *  Types
 */

typedef struct
{
    uint16_t elem_size;
    uint16_t elem_count;
    uint16_t offset;
    void   * type_map;
    uint16_t type_count;
} type_map_t;


/*
 *  Functions
 */

void strans_reverse_bytes
    (
    uint8_t * data,
    uint8_t   cnt
    );

void strans_reverse_bytes_by_map
    (
    void       * data,
    type_map_t * map,
    uint16_t     map_count
    );

#endif