#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "khash.h"

#define Max(a, b) ( ( (a) > (b) ) ? (a) : (b) )

typedef struct {
    char ch[5];
    char sym[32];
    size_t idx;
} TChinese;

typedef struct {
    TChinese *list;
    size_t    cap;
    size_t    len;
} TCList;

KHASH_MAP_INIT_STR(tchinese_map, size_t)

int main( int argc, char *argv[] ) {
    if ( argc < 3 ) {
        fprintf( stdout, "Tip: cipher.exe <shift> <Options>\n" );
        fprintf( stdout, "Options:\n* -d decode the string.\n* -e encode the string.\n" );
        return 0;
    }

    #ifdef _WIN32
    SetConsoleCP( CP_UTF8 );
    SetConsoleOutputCP( CP_UTF8 );
    #endif
    
    // Loading Dictionary
    khash_t(tchinese_map) *h = kh_init( tchinese_map );

    FILE *words_file = fopen( "word.csv", "rb" );
    if ( !words_file ) {
        fprintf( stderr, "Word.csv file non exist.\n" );
        kh_destroy( tchinese_map, h );
        return 1;
    }
    TCList tclist = { .list = NULL, .cap = 0, .len = 0 };

    size_t max_same = 0, current_same = 1;
    char line[128], last_sym[36];
    while ( fgets( line, sizeof(line), words_file ) ) {
        line[strcspn( line, "\r\n" )] = 0;
        if ( line[0] == 0 ) continue;

        unsigned char c = (unsigned char)line[0];
        size_t n = c < 0XC0 ? 1 : c < 0XE0 ? 2 : c < 0XF0 ? 3 : 4;
        if ( line[n] != ',' ) continue;

        TChinese tp = { .ch = {0}, .sym = {0}, .idx = tclist.len };
        memcpy( tp.ch, line, n );
        snprintf( tp.sym, sizeof( tp.sym ), "%s", line + n + 1 );
        if ( tclist.len == 0 ) strcpy( last_sym, tp.sym );
        else {
            if ( strcmp( tp.sym, last_sym ) == 0 ) ++current_same;
            else {
                strcpy( last_sym, tp.sym );
                max_same = Max( max_same, current_same );
                current_same = 1;
            }
        }

        khiter_t k = kh_get( tchinese_map, h, tp.ch );
        if ( k != kh_end( h ) ) continue;
        
        if ( tclist.cap < tclist.len + 1 ) {
            size_t size = 2;
            while ( size < tclist.len + 1 ) size *= 2;
            TChinese *tp_list = (TChinese *)realloc( tclist.list, size*sizeof(TChinese) );
            if ( !tp_list ) {
                fprintf( stderr, "Out of Memory for TChinese.\n" );
                break;
            }
            tclist.list = tp_list;
            tclist.cap = size;
        }
        tclist.list[tclist.len] = tp;

        char *key = strdup( tp.ch );
        if ( !key ) {
            fprintf( stderr, "Out of Memory for key.\n" );
            break;
        }

        int ret = 0;
        k = kh_put( tchinese_map, h, key, &ret );
        if ( ret < 0 ) {
            free( key );
            fprintf( stderr, "Error for Khash function.\n" );
            break;
        }
        kh_val( h, k ) = tclist.len;

        ++tclist.len;
    }
    fclose( words_file );
    fprintf( stdout, "Successfully load [%lld] words.\n", tclist.len );
    fprintf( stdout, "Tip you shall choose shift > [%lld] < [%lld] that will be better.\n", max_same, tclist.len-max_same );
    // End of Loading Dictionary

    char *_ = NULL;
    long long shift = strtoll( argv[1], &_, 10 );
    if ( _ == argv[1] ) {
        fprintf( stderr, "Error for stdtoll().\n" );
        return 1;
    }
    shift %= (long long)tclist.len;
    if ( strcmp( argv[2], "-d" ) == 0 ) shift = -shift;
    else if ( strcmp( argv[2], "-e" ) != 0 ) {
        fprintf( stderr, "Unknow Option: [%s].\n", argv[2] );
        fprintf( stdout, "Options:\n* -d decode the string.\n* -e encode the string.\n" );
        return 1;
    }
    if ( shift < 0 ) shift += (long long)tclist.len;

    char str[1024];
    while ( fgets( str, sizeof(str), stdin ) ) {
        str[strcspn( str, "\r\n" )] = 0;
        if ( str[0] == 0 ) continue;

        if ( strcmp( str, "<88224466AB>" ) == 0 ) break; // 上上下下左左右右AB
        size_t str_len = strlen( str );
        
        for ( size_t i = 0; i < str_len; ) {
            unsigned char c = (unsigned char)str[i];
            size_t n = c < 0XC0 ? 1 : c < 0XE0 ? 2 : c < 0XF0 ? 3 : 4;
            
            char ch[5] = {0};
            memcpy( ch, str+i, n );
            
            i += n;
            
            khiter_t k = kh_get( tchinese_map, h, ch );
            if ( k == kh_end( h ) ) {
                fputs( ch, stdout );
                continue;
            }
            size_t indx = ( kh_val( h, k ) + (size_t)shift ) % tclist.len;
            fputs( tclist.list[indx].ch, stdout );
        }
        putchar( '\n' );
    }

    for ( khint_t k = kh_begin( h ); k != kh_end( h ); ++k ) {
        if ( kh_exist( h, k ) ) free( (char *)kh_key( h, k ) );
    }
    kh_destroy( tchinese_map, h );
    free( tclist.list );
    return 0;
}