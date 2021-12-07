////////////////////////////////////////////////////////////////////////////////
//
/// LSU EE 4755 Fall 2021 Homework 1
//

 /// Assignment  https://www.ece.lsu.edu/koppel/v/2021/hw01.pdf

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
  //     /home/faculty/koppel/pub/ee4755/hw/2021/hw01
  //     to a directory ~/hw01 in your class account. (~ is your home
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
 ///   Complete insert_at so that output o is set to ia with ib inserted at pos. 
 ///
//
//     [ ] Make sure that the testbench does not report errors.
//     [ ] Module must be synthesizable. Use command: genus -files syn.tcl
//
//     [ ] Do not use procedural code.
//     [ ] Do not use the << or >> operators (or anything similar).
//     [ ] Use the shift and mask modules to provide shifted values
//         and bitmasks.
//
//     [ ] Don't assume any particular parameter value.
//
//     [ ] Code must be written clearly.
//     [ ] Pay attention to cost and performance.


module insert_at
  #( int wa = 20, wb = 10, wo = wa+wb, walg = $clog2(wa+1) )
   ( output logic [wo-1:0] o,
     input uwire [wa-1:0] ia,
     input uwire [wb-1:0] ib,
     input uwire [walg-1:0] pos );

   // calculate mask
   uwire [wo-1:0] mask_low, mask_high;
   mask_lsb #(wo,walg) m1( mask_low, pos );
   mask_msb #(wo,walg) m2( mask_high, walg'(($size(ia)+$size(ib))-pos-3) );

   uwire [wo-1:0] lmask = ia & mask_low;
   uwire [wo-1:0] ia_shifted;
   shift_left #(wa,wo,walg) sl2( ia_shifted, ia, walg'(3) );
   uwire [wo-1:0] rmask = ia_shifted & mask_high;
   uwire [wo-1:0] ia_masked = lmask | rmask;

   uwire [wo-1:0] ib_at_pos;
   shift_left #(wb,wo,walg) sl1( ib_at_pos, ib, pos );

   assign o = ia_masked | ib_at_pos;
endmodule


module shift_left
  #( int wi = 4, wo = wi, wolg = $clog2(wo) )
   ( output uwire [wo-1:0] o,
     input uwire [wi-1:0] i,
     input uwire [wolg-1:0] amt );
   assign o = i << amt;
endmodule

module shift_right
  #( int wi = 4, wo = wi, wolg = $clog2(wo) )
   ( output uwire [wo-1:0] o,
     input uwire [wi-1:0] i,
     input uwire [wolg-1:0] amt );
   assign o = i >> amt;
endmodule

module mask_lsb
  #( int wo = 6, wp = $clog2(wo+1) )
   ( output logic [wo-1:0] o, input uwire [wp-1:0] n1 );
   always_comb for ( int i=0; i<wo; i++ ) o[i] = i < n1;
endmodule

module mask_msb
  #( int wo = 6, wp = $clog2(wo+1) )
   ( output logic [wo-1:0] o, input uwire [wp-1:0] n1 );
   always_comb for ( int i=0; i<wo; i++ ) o[wo-i-1] = i < n1;
endmodule


//////////////////////////////////////////////////////////////////////////////
/// Testbench Code


// cadence translate_off

module testbench;

   localparam int wa = 8;
   localparam int wb = 3;
   localparam int wo = wa+wb;
   localparam int walg = $clog2(wa+1);

   localparam int n_tests = (wa+1) * 10;

   logic [wa-1:0] ia;
   logic [wb-1:0] ib;
   uwire [wo-1:0] o;
   logic [walg-1:0] pos;

   insert_at #(wa,wb) iat(o, ia, ib, pos);

   initial begin

      automatic int n_err = 0;

      for ( int tn = 0; tn < n_tests; tn++ ) begin

         automatic int rnd = tn / (wa+1);

         logic [wo-1:0] o_shadow;

         pos = tn % (wa+1);
         case ( rnd )
            0: begin ia = -1; ib = 0; end
            1: begin ia = 0;  ib = -1; end
            default: {ia,ib} = {$random};
         endcase

         #1;

         for ( int i=0; i<pos; i++ ) o_shadow[i] = ia[i];
         for ( int i=0; i<wb; i++ ) o_shadow[i+pos] = ib[i];
         for ( int i=pos; i<wa; i++ ) o_shadow[i+wb] = ia[i];

         if ( o_shadow !== o ) begin
            n_err++;
            if ( n_err < 6 )
              $write("Error for ia=%b  ib=%b  pos=%d  %b != %b (correct)\n",
                     ia, ib, pos, o, o_shadow);
         end

      end

      $write("Done with %0d tests, %0d errors found.\n",
             n_tests, n_err);

   end

endmodule

// cadence translate_on
