// The C codes generate the cvc files.

#include<stdio.h>

// Define the number of rounds
#define round 8

int sbox[16] = { 0xe, 0x4, 0xb, 0x1, 0x7, 0x9, 0xc, 0xa, 0xd, 0x2, 0x0, 0xf, 0x8, 0x5, 0x3, 0x6 } ;


main()
{
    int r ;
    int i, j ;

    FILE *fp;
    fp = fopen( "differential-active-sbox-8.cvc", "w" ) ;


    for( r=0; r<round; r++ )
    {

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "before_sbox_value1_%d_%d: BITVECTOR(4) ;\n", r, i ) ;
            fprintf( fp, "before_sbox_value2_%d_%d: BITVECTOR(4) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "after_sbox_value1_%d_%d: BITVECTOR(4) ;\n", r, i ) ;
            fprintf( fp, "after_sbox_value2_%d_%d: BITVECTOR(4) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "before_sbox_difference_%d_%d: BITVECTOR(4) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "after_sbox_difference_%d_%d: BITVECTOR(4) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++ )
        {
            fprintf( fp, "before_rotation_difference_%d_%d: BITVECTOR(16) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++ )
        {
            fprintf( fp, "after_rotation_difference_%d_%d: BITVECTOR(16) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++ )
        {
            fprintf( fp, "after_blockxor_difference_%d_%d: BITVECTOR(16) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "flag_%d_%d: BITVECTOR(12) ;\n", r, i ) ;
        }

        fprintf( fp, "\n" ) ;


    }

    for( i=0; i<16; i++ )
    {
        fprintf( fp, "before_sbox_difference_%d_%d: BITVECTOR(4) ;\n", round, i ) ;
    }

    fprintf( fp, "\n" ) ;

    fprintf( fp, "total_num: BITVECTOR(12) ;\n", r, i ) ;

    fprintf( fp, "\n" ) ;


    for( r=0; r<round; r++ )
    {

        for( i=0; i<16; i++ )
        {
            for( j=0; j<16; j++ )
            {
                fprintf( fp, "ASSERT( ( before_sbox_value1_%d_%d = 0hex%x )=>( after_sbox_value1_%d_%d = 0hex%x ) ) ;\n", r, i, j, r, i, sbox[j] ) ;
                fprintf( fp, "ASSERT( ( before_sbox_value2_%d_%d = 0hex%x )=>( after_sbox_value2_%d_%d = 0hex%x ) ) ;\n", r, i, j, r, i, sbox[j] ) ;
            }
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "ASSERT( before_sbox_difference_%d_%d = BVXOR(before_sbox_value1_%d_%d,before_sbox_value2_%d_%d) ) ;\n", r, i, r, i, r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "ASSERT( after_sbox_difference_%d_%d = BVXOR(after_sbox_value1_%d_%d,after_sbox_value2_%d_%d) ) ;\n", r, i, r, i, r, i ) ;
        }

        fprintf( fp, "\n" ) ;

        fprintf( fp, "ASSERT( before_rotation_difference_%d_0 = after_sbox_difference_%d_2@after_sbox_difference_%d_3@after_sbox_difference_%d_0@after_sbox_difference_%d_1 ) ;\n", r, r, r, r, r ) ;
        fprintf( fp, "ASSERT( before_rotation_difference_%d_1 = after_sbox_difference_%d_6@after_sbox_difference_%d_7@after_sbox_difference_%d_4@after_sbox_difference_%d_5 ) ;\n", r, r, r, r, r ) ;
        fprintf( fp, "ASSERT( before_rotation_difference_%d_2 = after_sbox_difference_%d_10@after_sbox_difference_%d_11@after_sbox_difference_%d_8@after_sbox_difference_%d_9 ) ;\n", r, r, r, r, r ) ;
        fprintf( fp, "ASSERT( before_rotation_difference_%d_3 = after_sbox_difference_%d_14@after_sbox_difference_%d_15@after_sbox_difference_%d_12@after_sbox_difference_%d_13 ) ;\n", r, r, r, r, r ) ;

        fprintf( fp, "\n" ) ;

        fprintf( fp, "ASSERT( after_rotation_difference_%d_0 = before_rotation_difference_%d_0[14:0]@before_rotation_difference_%d_0[15:15] ) ;\n", r, r, r ) ;
        fprintf( fp, "ASSERT( after_rotation_difference_%d_1 = before_rotation_difference_%d_1[11:0]@before_rotation_difference_%d_1[15:12] ) ;\n", r, r, r ) ;
        fprintf( fp, "ASSERT( after_rotation_difference_%d_2 = before_rotation_difference_%d_2[6:0]@before_rotation_difference_%d_2[15:7] ) ;\n", r, r, r ) ;
        fprintf( fp, "ASSERT( after_rotation_difference_%d_3 = before_rotation_difference_%d_3[8:0]@before_rotation_difference_%d_3[15:9] ) ;\n", r, r, r ) ;

        fprintf( fp, "\n" ) ;

        fprintf( fp, "ASSERT( after_blockxor_difference_%d_1 = BVXOR(after_rotation_difference_%d_1,after_rotation_difference_%d_3) );\n", r, r, r ) ;
        fprintf( fp, "ASSERT( after_blockxor_difference_%d_2 = BVXOR(after_rotation_difference_%d_0,after_rotation_difference_%d_2) );\n", r, r, r ) ;
        fprintf( fp, "ASSERT( after_blockxor_difference_%d_0 = BVXOR(after_rotation_difference_%d_0,after_blockxor_difference_%d_1) );\n", r, r, r ) ;
        fprintf( fp, "ASSERT( after_blockxor_difference_%d_3 = BVXOR(after_rotation_difference_%d_3,after_blockxor_difference_%d_2) );\n", r, r, r ) ;

        fprintf( fp, "\n" ) ;

        for( i=0; i<4; i++)
        {
            for( j=0; j<4; j++ )
            {
                fprintf( fp, "ASSERT( before_sbox_difference_%d_%d = after_blockxor_difference_%d_%d[%d:%d] ) ;\n", r+1, j+4*i, r, i, 3+4*j, 0+4*j ) ;
            }
        }

        fprintf( fp, "\n" ) ;

        for( i=0; i<16; i++ )
        {
            fprintf( fp, "ASSERT( IF ( before_sbox_difference_%d_%d=0hex0 AND after_sbox_difference_%d_%d=0hex0 ) THEN flag_%d_%d=0hex000 ELSE flag_%d_%d=0hex001 ENDIF ) ;\n", r, i, r, i, r, i, r, i ) ;
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

    // Objective Function: Limit the number of active S-Boxes
    fprintf( fp, "ASSERT( total_num = 0hex002 ) ;\n" ) ;


    fprintf( fp, "QUERY(FALSE) ;\n" ) ;
	  fprintf( fp, "COUNTEREXAMPLE ;\n" ) ;

}
