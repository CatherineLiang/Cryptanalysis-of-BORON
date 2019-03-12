#include<stdio.h>

#define round 10

int sbox[16] = { 0xe, 0x4, 0xb, 0x1, 0x7, 0x9, 0xc, 0xa, 0xd, 0x2, 0x0, 0xf, 0x8, 0x5, 0x3, 0x6 } ;

int linear_dist[16][16] = {
{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
{0, 0, 0, 4, 0, 0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2} ,
{0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 4, 4} ,
{0, 0, 2, 2, 2, 2, 4, 0, 2, 2, 0, 0, 0, 4, 2, 2} ,
{0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 0, 0, 4} ,
{0, 0, 0, 4, 0, 0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2} ,
{0, 4, 2, 2, 2, 2, 4, 0, 0, 0, 2, 2, 2, 2, 0, 0} ,
{0, 4, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 4, 0, 2, 2} ,
{0, 0, 0, 0, 0, 4, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2} ,
{0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0} ,
{0, 0, 2, 2, 2, 2, 4, 0, 2, 2, 0, 4, 0, 0, 2, 2} ,
{0, 0, 2, 2, 2, 2, 0, 0, 4, 4, 2, 2, 2, 2, 0, 0} ,
{0, 0, 0, 0, 0, 4, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2} ,
{0, 0, 4, 0, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 0} ,
{0, 4, 2, 2, 2, 2, 0, 0, 2, 2, 4, 0, 0, 0, 2, 2} ,
{0, 4, 2, 2, 2, 2, 4, 0, 0, 0, 2, 2, 2, 2, 0, 0}
} ;



main()
{
    int r ;
    int i, j ;

    FILE *fp;
    fp = fopen( "new_linear_trail-10.cvc", "w" ) ;


    fprintf( fp, "linear_dist: ARRAY BITVECTOR(8) OF BITVECTOR(8) ;\n" ) ;

    fprintf( fp, "\n" ) ;

    for( r=0; r<round; r++ )
    {

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "before_sbox_mask_%d_%d: BITVECTOR(4) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "after_sbox_mask_%d_%d: BITVECTOR(4) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++ )
        {
            fprintf( fp, "before_rotation_mask_%d_%d: BITVECTOR(16) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++ )
        {
            fprintf( fp, "after_rotation_mask_%d_%d: BITVECTOR(16) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++ )
        {
            fprintf( fp, "after_blockxor_mask_%d_%d: BITVECTOR(16) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++ )
        {
            fprintf( fp, "branch_%d_%d_up: BITVECTOR(16) ;\n", r, i ) ;
            fprintf( fp, "branch_%d_%d_down: BITVECTOR(16) ;\n", r, i ) ;
            fprintf( fp, "branch_%d_%d_another: BITVECTOR(16) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++ )
        {
            fprintf( fp, "xor_%d_%d_up: BITVECTOR(16) ;\n", r, i ) ;
            fprintf( fp, "xor_%d_%d_down: BITVECTOR(16) ;\n", r, i ) ;
            fprintf( fp, "xor_%d_%d_another: BITVECTOR(16) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "flag_%d_%d: BITVECTOR(12) ;\n", r, i ) ;//sign of active s-boxes
        }

        fprintf( fp, "\n" ) ;


        for( i=0; i<16; i++ )
        {
            fprintf( fp, "bias_%d_%d: BITVECTOR(12) ;\n", r, i ) ;//bias of s-boxes
        }

        fprintf( fp, "\n" ) ;

    }


    for( i=0; i<16; i++ )
    {
        fprintf( fp, "before_sbox_mask_%d_%d: BITVECTOR(4) ;\n", round, i ) ;
    }

    fprintf( fp, "\n" ) ;

    fprintf( fp, "total_num: BITVECTOR(12) ;\n" ) ; //number of active s-boxes

    fprintf( fp, "flag_tail: BITVECTOR(12) ;\n" ) ; //number of active s-boxes from the last round

    fprintf( fp, "sum_bias: BITVECTOR(12) ;\n" ) ; //the sum of bias of the whole trail

    fprintf( fp, "total_bias: BITVECTOR(12) ;\n" ) ; //the bias of the whole trail

    fprintf( fp, "\n" ) ;

    for( i=0; i<16; i++ )
    {
        for( j=0; j<16; j++ )
        {
            fprintf( fp, "ASSERT( linear_dist[0hex%x%x]=0hex%02x ) ;\n", i, j, linear_dist[i][j] ) ;
        }
    }

    fprintf( fp, "\n" ) ;

    for( r=0; r<round; r++ )
    {

        fprintf( fp, "ASSERT( before_rotation_mask_%d_0 = after_sbox_mask_%d_1@after_sbox_mask_%d_0@after_sbox_mask_%d_3@after_sbox_mask_%d_2 ) ;\n", r, r, r, r, r ) ;
        fprintf( fp, "ASSERT( before_rotation_mask_%d_1 = after_sbox_mask_%d_5@after_sbox_mask_%d_4@after_sbox_mask_%d_7@after_sbox_mask_%d_6 ) ;\n", r, r, r, r, r ) ;
        fprintf( fp, "ASSERT( before_rotation_mask_%d_2 = after_sbox_mask_%d_9@after_sbox_mask_%d_8@after_sbox_mask_%d_11@after_sbox_mask_%d_10 ) ;\n", r, r, r, r, r ) ;
        fprintf( fp, "ASSERT( before_rotation_mask_%d_3 = after_sbox_mask_%d_13@after_sbox_mask_%d_12@after_sbox_mask_%d_15@after_sbox_mask_%d_14 ) ;\n", r, r, r, r, r ) ;

        fprintf( fp, "\n" ) ;

        fprintf( fp, "ASSERT( after_rotation_mask_%d_0 = before_rotation_mask_%d_0[14:0]@before_rotation_mask_%d_0[15:15] ) ;\n", r, r, r ) ;
        fprintf( fp, "ASSERT( after_rotation_mask_%d_1 = before_rotation_mask_%d_1[11:0]@before_rotation_mask_%d_1[15:12] ) ;\n", r, r, r ) ;
        fprintf( fp, "ASSERT( after_rotation_mask_%d_2 = before_rotation_mask_%d_2[8:0]@before_rotation_mask_%d_2[15:9] ) ;\n", r, r, r ) ;
        fprintf( fp, "ASSERT( after_rotation_mask_%d_3 = before_rotation_mask_%d_3[6:0]@before_rotation_mask_%d_3[15:7] ) ;\n", r, r, r ) ;

        fprintf( fp, "\n" ) ;


        for( i=0; i<4; i++ )
        {
            fprintf( fp, "ASSERT( branch_%d_%d_another = BVXOR( branch_%d_%d_up, branch_%d_%d_down ) ) ;\n", r, i, r, i, r, i ) ;
        }

        for( i=0; i<4; i++ )
        {
            fprintf( fp, "ASSERT( xor_%d_%d_up = xor_%d_%d_down ) ;\n", r, i, r, i ) ;
            fprintf( fp, "ASSERT( xor_%d_%d_up = xor_%d_%d_another ) ;\n", r, i, r, i ) ;
        }


        fprintf( fp, "ASSERT( after_rotation_mask_%d_0 = branch_%d_0_up );\n", r, r ) ;
        fprintf( fp, "ASSERT( after_rotation_mask_%d_1 = xor_%d_1_up );\n", r, r ) ;
        fprintf( fp, "ASSERT( after_rotation_mask_%d_2 = xor_%d_2_up );\n", r, r ) ;
        fprintf( fp, "ASSERT( after_rotation_mask_%d_3 = branch_%d_3_up );\n", r, r ) ;

        fprintf( fp, "\n" ) ;

        fprintf( fp, "ASSERT( after_blockxor_mask_%d_0 = xor_%d_0_down );\n", r, r ) ;
        fprintf( fp, "ASSERT( after_blockxor_mask_%d_1 = branch_%d_1_down );\n", r, r ) ;
        fprintf( fp, "ASSERT( after_blockxor_mask_%d_2 = branch_%d_2_down );\n", r, r ) ;
        fprintf( fp, "ASSERT( after_blockxor_mask_%d_3 = xor_%d_3_down );\n", r, r ) ;

        fprintf( fp, "\n" ) ;

        fprintf( fp, "ASSERT( branch_%d_0_another = xor_%d_2_another );\n", r, r ) ;
        fprintf( fp, "ASSERT( branch_%d_1_another = xor_%d_0_another );\n", r, r ) ;
        fprintf( fp, "ASSERT( branch_%d_2_another = xor_%d_3_another );\n", r, r ) ;
        fprintf( fp, "ASSERT( branch_%d_3_another = xor_%d_1_another );\n", r, r ) ;

        fprintf( fp, "\n" ) ;

        fprintf( fp, "ASSERT( branch_%d_0_down = xor_%d_0_up );\n", r, r ) ;
        fprintf( fp, "ASSERT( branch_%d_1_up = xor_%d_1_down );\n", r, r ) ;
        fprintf( fp, "ASSERT( branch_%d_2_up = xor_%d_2_down );\n", r, r ) ;
        fprintf( fp, "ASSERT( branch_%d_3_down = xor_%d_3_up );\n", r, r ) ;

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++)
        {
            for( j=0; j<4; j++ )
            {
                fprintf( fp, "ASSERT( before_sbox_mask_%d_%d = after_blockxor_mask_%d_%d[%d:%d] ) ;\n", r+1, j+4*i, r, i, 3+4*j, 0+4*j ) ;
            }
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "ASSERT( IF ( before_sbox_mask_%d_%d=0hex0 AND after_sbox_mask_%d_%d=0hex0 ) THEN flag_%d_%d=0hex000 ELSE flag_%d_%d=0hex001 ENDIF ) ;\n", r, i, r, i, r, i, r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {

            fprintf( fp, "ASSERT( ( linear_dist[before_sbox_mask_%d_%d@after_sbox_mask_%d_%d]=0hex00 ) => ( bias_%d_%d=0hex007 ) ) ;\n", r, i, r, i, r, i ) ;
            fprintf( fp, "ASSERT( ( linear_dist[before_sbox_mask_%d_%d@after_sbox_mask_%d_%d]=0hex02 ) => ( bias_%d_%d=0hex003 ) ) ;\n", r, i, r, i, r, i ) ;
            fprintf( fp, "ASSERT( ( linear_dist[before_sbox_mask_%d_%d@after_sbox_mask_%d_%d]=0hex04 ) => ( bias_%d_%d=0hex002 ) ) ;\n", r, i, r, i, r, i ) ;
            fprintf( fp, "ASSERT( ( linear_dist[before_sbox_mask_%d_%d@after_sbox_mask_%d_%d]=0hex08 ) => ( bias_%d_%d=0hex000 ) ) ;\n", r, i, r, i, r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "ASSERT( NOT( bias_%d_%d=0hex007 ) ) ;\n", r, i

                     ) ;
        }

        fprintf( fp, "\n" ) ;

    }


    fprintf( fp, "ASSERT( total_num = BVPLUS(12" ) ;

    for( r=0; r<round; r++ )
    {
        for( i=0; i<16; i++ )
        {
            fprintf( fp, ", flag_%d_%d", r, i ) ;
        }
    }

    fprintf( fp, " ) ) ; \n" ) ;



    fprintf( fp, "ASSERT( flag_tail = BVPLUS(12" ) ;

    for( i=0; i<16; i++ )
    {
        fprintf( fp, ", flag_%d_%d", round-1, i ) ;
    }

    fprintf( fp, " ) ) ; \n" ) ;


    fprintf( fp, "ASSERT( sum_bias = BVPLUS(12, 0hex001" ) ;

    for( r=0; r<round; r++ )
    {
        for( i=0; i<16; i++ )
        {
            fprintf( fp, ", bias_%d_%d", r, i ) ;
        }
    }

    fprintf( fp, " ) ) ; \n" ) ;


    fprintf( fp, "ASSERT( total_bias = BVSUB(12, sum_bias, total_num ) ) ;\n" ) ;

    fprintf( fp, "ASSERT( total_bias = 0hex00c ) ;\n" ) ;


    fprintf( fp, "QUERY(FALSE) ;\n" ) ;
	  fprintf( fp, "COUNTEREXAMPLE ;\n" ) ;



}
