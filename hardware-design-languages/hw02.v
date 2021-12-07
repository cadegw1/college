////////////////////////////////////////////////////////////////////////////////
//
/// LSU EE 4755 Fall 2021 Homework 2
//

 /// Assignment  https://www.ece.lsu.edu/koppel/v/2021/hw02.pdf

 /// Instructions:
  //
  // (1) Find the undergraduate workstation laboratory, room 2241 Patrick
  //     F. Taylor Hall. Machines to use are in the back.
  //
  // (☣) Practice Social Distancing:
  //     - Keep your mask on and over your nostrils.
  //     - Don't assume that those around you live only with young
  //       and healthy people.
  //     - If you must take off your mask for a short period of time
  //       do so at least 2 meters from the closest person.
  //     - Don't forget that it is often spread by those who don't
  //       know they are infectious.
  //
  // (2) Locate your account.  If you did not get an account please
  //     E-mail: koppel@ece.lsu.edu
  //
  // (3) Log in to a Linux workstation.
  //
  // (4) If you haven't already, follow the account setup instructions here:
  //     https://www.ece.lsu.edu/koppel/v/proc.html
  //
  // (5) Copy this assignment, local path name
  //     /home/faculty/koppel/pub/ee4755/hw/2021/hw02
  //     to a directory ~/hw02 in your class account. (~ is your home
  //     directory.) Use this file for your solution.
  ///      BE SURE THAT YOUR FILE IS CORRECTLY NAMED AND IN THE RIGHT PLACE.
  //
  // (6) Find the problems in this file and solve them.
  //
  //     Your entire solution should be in this file.
  //
  //     Do not change module names.
  //
  // (7) Your solution will automatically be copied from your account by
  //     the TA-bot.


 /// Additional Resources
  //
  // Verilog Documentation
  //    The Verilog Standard
  //      https://ieeexplore.ieee.org/document/8299595/
  //    Introductory Treatment (Warning: Does not include SystemVerilog)
  //      Brown & Vranesic, Fundamentals of Digital Logic with Verilog, 3rd Ed.
  //
  // Account Setup and Emacs (Text Editor) Instructions
  //      https://www.ece.lsu.edu/koppel/v/proc.html
  //      To learn Emacs look for Emacs tutorial.
  //


`default_nettype none


//////////////////////////////////////////////////////////////////////////////
///  Problem 1
//
 ///   Complete nn_sparse so that it computes both dense (fmt=4'b1111)
 ///   and sparse (fmt= 4'b1100, 4'b0110, 4'b1010, etc.) products.
 ///
//
//     [ ] Only modify nn_sparse.
//
//     [ ] Make sure that the testbench does not report errors.
//     [ ] Module must be synthesizable. Use command: genus -files syn.tcl
//
//     [ ] To achieve the fastest speed a sparse product computation
//         should not go through two adders.
//
//     [ ] Don't assume any particular parameter values.
//
//     [ ] Code must be written clearly.
//     [ ] Pay attention to cost and performance.


module nn_sparse
  #( int nn = 4, wexp = 6, wsig_ac = 15, wsig_in = 10, wsig_wd = 6,
     wo = 1 + wexp + wsig_ac,
     wi = 1 + wexp + wsig_in,
     ww = nn * ( 1 + wexp + wsig_wd ) )
   ( output logic [wo-1:0] o,
     input uwire [wi-1:0] i[nn],
     input uwire [ww-1:0] w,
     input uwire [nn-1:0] fmt );

   // Compute size of significand of sparse weights.
   localparam int wsig_ws = 2 * wsig_wd + wexp + 1;

   // Separate wd into dense weights.
   localparam int wwd = ww / nn;
   uwire [3:0][wwd-1:0] wd;
   assign wd = w;

   // Compute result for dense weights.
   uwire [wo-1:0] acc1, acc2;
   nn2 #(wexp,wsig_in,wsig_wd,wsig_ac) nn2d1(acc1, i[0], i[1], wd[0], wd[1]);
   nn2 #(wexp,wsig_in,wsig_wd,wsig_ac) nn2d2(acc2, i[2], i[3], wd[2], wd[3]);
   fp_add #(wexp,wsig_ac) add(o,acc1,acc2);

endmodule

module nn2
  #( int wexp = 9, wsig_in = 10, wsig_w = 5, wsig_ac = 12,
     wi = 1 + wexp + wsig_in,
     ww = 1 + wexp + wsig_w,
     wo = 1 + wexp + wsig_ac)
   ( output uwire [wo-1:0] o,
     input uwire [wi-1:0] i0, i1,
     input uwire [ww-1:0] w0, w1 );

   uwire [wo-1:0] p0, p1;
   hy_mult #(wexp, wsig_in, wsig_w, wsig_ac) m0(p0,i0,w0);
   hy_mult #(wexp, wsig_in, wsig_w, wsig_ac) m1(p1,i1,w1);
   fp_add #(wexp,wsig_ac) a(o,p0,p1);

endmodule

module fp_add
  #( int wexp = 3, wsig = 50, w = 1 + wexp + wsig )
   ( output uwire [w-1:0] sum,
     input uwire [w-1:0] i0, i1 );

   uwire [7:0] s;
   localparam logic [2:0] rnd_to_0 = 3'b1;

   CW_fp_add #( .sig_width(wsig), .exp_width(wexp), .ieee_compliance(0))
   a(.a(i0),.b (i1), .rnd (rnd_to_0), .z (sum), .status (s) );

endmodule

module hy_mult
  #( int wexp = 5, int wsig_a = 6, int wsig_b = 7,
     int wsig_p = wsig_a + wsig_b )
   ( output uwire [wexp+wsig_p:0] prod,
     input uwire [wexp+wsig_a:0] a,
     input uwire [wexp+wsig_b:0] b );

   uwire [7:0] s;
   localparam logic [2:0] rnd_to_0 = 3'b1;
   localparam logic [2:0] rnd_to_plus_inf = 3'b10;
   localparam logic [2:0] rnd_to_minus_inf = 3'b11;

   localparam int wm = 1 + wexp + wsig_p;
   localparam int wsig_diff_a = wsig_p - wsig_a;
   localparam int wsig_diff_b = wsig_p - wsig_b;
   uwire [wm-1:0] ea = wsig_diff_a >= 0
                  ? a << wsig_diff_a : a[wexp+wsig_a:-wsig_diff_a];
   uwire [wm-1:0] eb = wsig_diff_b >= 0
                  ? b << wsig_diff_b : b[wexp+wsig_b:-wsig_diff_b];

   CW_fp_mult #( .sig_width(wsig_p), .exp_width(wexp), .ieee_compliance(0))
   U1(.a(ea),.b (eb), .rnd (rnd_to_0), .z (prod), .status (s) );

endmodule


//////////////////////////////////////////////////////////////////////////////
/// Testbench Code


// cadence translate_off

virtual class conv #(int wexp=6, wsig=10);
   // Convert between real and fp types using parameter-provided
   // exponent and significand sizes.

   localparam int w = 1 + wexp + wsig;
   localparam int bias_r = ( 1 << 11 - 1 ) - 1;
   localparam int w_sig_r = 52;
   localparam int w_exp_r = 11;
   localparam int bias_h = ( 1 << wexp - 1 ) - 1;

   static function logic [w-1:0] rtof( real r );
      logic [wsig-1:0] sig_f;
      logic [w_sig_r-wsig-1:0] sig_x;
      logic [w_exp_r-1:0] exp_r;
      logic sign_r;
      { sign_r, exp_r, sig_f, sig_x } = $realtobits(r);
      rtof = !r ? 0 : { sign_r, wexp'( exp_r + bias_h - bias_r ), sig_f };
   endfunction

   static function real ftor( logic [w-1:0] f );
      ftor = !f ? 0.0
        : $bitstoreal
          ( { f[w-1],
              w_exp_r'( bias_r + f[w-2:wsig] - bias_h ),
              f[wsig-1:0], (w_sig_r-wsig)'(0) } );
   endfunction

endclass

function real fabs(real a);
      fabs = a < 0 ? -a : a;
endfunction

function int min( int a, b );
      min = a < b ? a : b;
endfunction

function int min3( int a, b, c );
      automatic int ab = a < b ? a : b;
      min3 = ab < c ? ab : c;
endfunction



module testbench_nn_sparse;

   localparam int npsets = 3;
   localparam int pset[npsets][4] =
              '{ {5, 20, 15, 4}, {6, 18, 10, 5}, {6, 18, 12, 3} };
   // wexp, wsig_ac, wsig_in, wsig_wd
   logic done[npsets:0];

   initial done[0] = 1;

   for ( genvar i = 0; i<npsets; i++ )
      testbench_nn_sparse_p
        #(pset[i][0],pset[i][1],pset[i][2],pset[i][3])
        tb(done[i+1],done[i]);


endmodule

module testbench_nn_sparse_p
  #( int wexp = 5, wsig_ac = 10, wsig_in = 6, wsig_wd = 4 )
   ( output logic done, input uwire start );

   localparam int ni = 4;
   localparam int wo = 1 + wexp + wsig_ac;
   localparam int wi = 1 + wexp + wsig_in;
   localparam int ww = ni * ( 1 + wexp + wsig_wd );

   localparam int wsig_ws = 2 * wsig_wd + wexp + 1;
   localparam int ws = 1 + wexp + wsig_ws;
   localparam int wd = 1 + wexp + wsig_wd;

   localparam real tol_s = real'(2) / ( 1 << min(wsig_in,wsig_ws) );
   localparam real tol_d = real'(2) / ( 1 << wsig_wd );

   localparam int n_tests = 5000;
   localparam real hot_val[] = { 1, 2, 0.1, 10.1 };
   localparam int n_one_hot = 4;
   localparam int n_two_hot = n_one_hot;
   initial if ( n_one_hot != hot_val.size() )
     $fatal(1,"Fix n_one_hot and file a Cadence bug.");

   logic [wo-1:0] o;
   logic [wi-1:0] ia[ni];
   logic [ww-1:0] wht;
   logic [ni-1:0] fmt;

   localparam logic [5:0][3:0] fmts =
              { 4'b11, 4'b110, 4'b1100, 4'b101, 4'b1010, 4'b1001 };

   nn_sparse #(ni, wexp, wsig_ac, wsig_in, wsig_wd) nnsp(o, ia, wht, fmt);

   initial begin

      automatic int n_errd = 0, n_errs = 0;
      automatic real max_diffs = 0, max_diffd = 0;
      automatic string abbrev =
             $sformatf("ex%0d,ac%0d,in%0d,wd%0d",wexp,wsig_ac,wsig_in,wsig_wd);
      wait ( start );
      $write("Testing %s: wexp=%0d, wsig_ac=%0d, wsig_in=%0d, wsig_wd=%0d\n",
             abbrev, wexp, wsig_ac, wsig_in, wsig_wd);

      for (int tn = 0; tn < n_tests; tn++ ) begin

         automatic int sidx = 0;
         automatic int hot = tn % 4;
         automatic int rnd = tn / 4;
         automatic int one_hot = rnd < n_one_hot;
         automatic int two_hot = !one_hot && rnd - n_one_hot < n_two_hot;
         automatic int sparse = one_hot || two_hot || {$random} & 1;

         automatic int h2 = ( hot + 1 + {$random}%3 ) % 4;

         real shadow_ia[4], shadow_w[4], shadow_o, diff, oreal, tol;
         real max_diff;
         logic [3:0][wd-1:0] wht4;
         logic [1:0][ws-1:0] wht2;
         fmt = one_hot || two_hot ? ( 1<<hot ) | ( 1<<h2 )
         : sparse ? fmts[{$random}%6] : 4'hf;
         tol = sparse ? tol_s : tol_d;
         shadow_o = 0;
         for ( int i=0; i<4; i++ ) begin
            automatic real iav = real'({$random}) / ( 1 << 30 );
            automatic real w = real'({$random}) / ( 1 << 30 );
            if ( one_hot || two_hot )
              begin
                 iav = 1.0 + real'(i)/10;
                 w = i == hot || two_hot && i == h2 ? hot_val[rnd] : 0;
              end
            shadow_w[i] = w;
            shadow_ia[i] = iav;
            wht4[i] = conv#(wexp,wsig_wd)::rtof(w);
            ia[i] = conv#(wexp,wsig_in)::rtof(iav);
            if ( sparse && fmt[i] ) wht2[sidx++] = conv#(wexp,wsig_ws)::rtof(w);
            if ( fmt[i] ) shadow_o += iav * w;
         end
         wht = sparse ? wht2 : wht4;
         #1;
         oreal = conv#(wexp,wsig_ac)::ftor(o);
         diff = fabs( shadow_o - oreal ) / fabs( shadow_o ? shadow_o : 1 );
         max_diff = sparse ? max_diffs : max_diffd;

         if ( ! ( diff < tol ) ) begin
            automatic int n_err = sparse ? ++n_errs : ++n_errd;
            if ( n_err < 5 || 0 && diff > max_diff ) begin
               automatic int ilast = fmt[3] ? 3 : fmt[2] ? 2 : 1;
               $write( "Error tn=%0d for fmt %4b  %h = %7.4f != %7.4f (correct)\n",
                       tn, fmt, o, oreal, shadow_o );
               $write( "      ");
               for ( int i=0; i<4; i++ )
                 if ( fmt[i] )
                   $write( "%.4f %.4f%s", shadow_ia[i], shadow_w[i],
                           i < ilast ? " + " : "\n");
               $write( "      ");
               for ( int i=0; i<4; i++ )
                 if ( fmt[i] )
                 $write( "%.4f     %s", shadow_ia[i] * shadow_w[i],
                         i < ilast ? " + " : "\n");
               if ( 0 )
                 $write( "      diff %.8f,  tol %.8f\n",diff,tol);

               // Feel free to modify or add to this to help with your solution.
               $write( "      acc1 = %h = %.4f\n",
                        nnsp.acc1, conv#(wexp,wsig_ac)::ftor(nnsp.acc1));

            end
         end

         if ( diff > max_diff ) begin
            if ( sparse ) max_diffs = diff; else max_diffd = diff;
         end

      end

      $write("Done with %s %0d tests, %0d, %0d  sp, den errors found.\n",
             abbrev, n_tests, n_errs, n_errd);
      $write("For %s  max diff %f, %f  sp, den.\n",
             abbrev, max_diffs, max_diffd);
      done = 1;

   end

endmodule


module testbench_hy;

   localparam int n_tests = 5;

   localparam int w_sig_a = 10;
   localparam int w_sig_b = 20;
   localparam int w_sig_p = 25;
   localparam int w_exp = 5;
   localparam int wa = 1 + w_exp + w_sig_a;
   localparam int wb = 1 + w_exp + w_sig_b;
   localparam int wp = 1 + w_exp + w_sig_p;
   localparam int bias_hy = ( 1 << w_exp - 1 ) - 1;
   localparam int bias_sr = ( 1 << 8 - 1 ) - 1;
   localparam int bias_r = ( 1 << 11 - 1 ) - 1;
   localparam int w_sig_r = 52;
   localparam int w_exp_r = 11;
   localparam int w_sig_min = min3( w_sig_a, w_sig_b, w_sig_p );
   localparam real tol = 1.0 / ( longint'(1) << w_sig_min );

   logic [wa-1:0] a;
   logic [wb-1:0] b;
   uwire [wp-1:0] prod;

   hy_mult #(w_exp,w_sig_a,w_sig_b,w_sig_p) hm1(prod,a,b);

   initial begin

      automatic int n_err = 0;
      automatic real diff_max = 0;

      for (int i=0; i<n_tests; i++ ) begin

         automatic real a_shadow = real'($random()) / (1<<31);
         automatic real b_shadow = real'($random()) / (1<<31);
         automatic real prod_correct = a_shadow * b_shadow;
         real prodf, diff;

         a = conv#(w_exp,w_sig_a)::rtof(a_shadow);
         b = conv#(w_exp,w_sig_b)::rtof(b_shadow);

         #1;

         prodf = conv#(w_exp,w_sig_p)::ftor( prod );
         diff = fabs( prodf - prod_correct );
         if ( diff > diff_max ) diff_max = diff;

         if ( ! ( diff < tol ) ) begin
            n_err++;
            if ( n_err < 4 )
              $write( "Error for %.3f * %.3f:  %.4f != %.4f (correct)\n",
                      a_shadow, b_shadow, prodf, prod_correct);

         end

      end

      $write("Done with hy %d tests, %d errors found. Max diff %f\n",
             n_tests, n_err, diff_max);

   end

endmodule

// cadence translate_on

`default_nettype wire
`include "/apps/linux/cadence/GENUS211/share/synth/lib/chipware/sim/verilog/CW/CW_fp_mult.v"
`include "/apps/linux/cadence/GENUS211/share/synth/lib/chipware/sim/verilog/CW/CW_fp_add.v"