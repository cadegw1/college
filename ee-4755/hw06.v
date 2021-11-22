////////////////////////////////////////////////////////////////////////////////
//
/// LSU EE 4755 Fall 2021 Homework 6
//  Cade Williams & Armando Castillo

 /// Assignment  https://www.ece.lsu.edu/koppel/v/2021/hw06.pdf

 /// Instructions:
  //
  // (1) Find the undergraduate workstation laboratory, room 2241 Patrick
  //     F. Taylor Hall. Machines to use are in the back.
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
  //     /home/faculty/koppel/pub/ee4755/hw/2021/hw06
  //     to a directory ~/hw06 in your class account. (~ is your home
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
 ///   Complete multi_step_pipe so that it computes the same value as
 ///   ms_functional, but does so in a pipelined fashion.
 ///
//
//     [ ] Only modify module multi_step_pipe.
//     [ ] Module must operate in pipelined fashion ..
//     [ ] .. meaning it should accept a new set of inputs each cycle ..
//     [ ] .. and provide the result several cycles later.
//     [ ] Be sure to pass the start signal from input to output.
//
//     [ ] Instantiate as many Chipware mult and add units as needed.
//     [ ] The critical path can go through at most one Chipware module.
//
//     [ ] Use SimVision to debug. Use command: xrun -gui hw06.v
//
//     [ ] Make sure that the testbench does not report errors.
//     [ ] Module must be synthesizable. Use command: genus -files syn.tcl
//
//     [ ] Code must be written clearly.
//     [ ] Pay attention to cost and performance.
//
//     [ ] Students can work in teams. List team members in this file

module multi_step_pipe
  ( output logic [31:0] result,   output logic ready,
    input uwire [31:0] v0, v1,    input uwire start, clk);

   localparam int nstages = 5; // Must be set to an appropriate value.

   localparam logic [2:0] rm = 0; // Rounding Mode

   uwire [7:0] mul_s[0:nstages]; 
   uwire [7:0] add_s[0:nstages];
   uwire [31:0] sum[0:2];
   uwire [31:0] prod[0:1];

   logic p_ready[0:nstages];
   logic [31:0] p_v0[0:nstages];
   logic [31:0] p_v1[0:nstages];
   logic [31:0] p_sum[0:4];
   logic [31:0] p_prod[0:1];

   CW_fp_mult m0(.a(v0), .b(v0), .rnd(3'b0), .z(sum[0]), .status(mul_s[0])); 

   CW_fp_mult m1(.a(p_v0[0]), .b(p_v1[0]), .rnd(3'b0), .z(prod[0]), .status(mul_s[1])); 
   CW_fp_add a1(.a(p_prod[0]), .b(p_sum[1]), .rnd(3'b0), .z(sum[1]),  .status(add_s[1]));

   CW_fp_mult m2(.a(p_v1[2]), .b(p_v1[2]), .rnd(3'b0), .z(prod[1]), .status(mul_s[2])); 
   CW_fp_add a2(.a(p_prod[1]), .b(p_sum[3]), .rnd(3'b0), .z(sum[2]),  .status(add_s[2]));

   always_ff @( posedge clk) begin
      p_sum[0] <= sum[0];
      p_sum[1] <= p_sum[0];
      p_sum[2] <= sum[1];
      p_sum[3] <= p_sum[2];
      p_sum[4] <= sum[2];
      p_prod[0] <= prod[0];
      p_prod[1] <= prod[1];
   end

   always_ff @( posedge clk ) begin
      p_ready[0] <= start;
      p_v0[0] <= v0;
      p_v1[0] <= v1;
      for( int stage = 0; stage < nstages; stage++) begin
         p_ready[stage + 1] <= p_ready[stage];
         p_v0[stage + 1] <= p_v0[stage];
         p_v1[stage + 1] <= p_v1[stage];
      end
   end

   assign result = p_sum[4];
   assign ready = p_ready[nstages - 1];

endmodule


 /// Non-Synthesizable Mag Module --- Complete, Don't Edit
// cadence translate_off
module multi_step_functional
  ( output shortreal mag,
    input shortreal v0, v1 );

   always_comb mag = v0 * v0 + v0 * v1 + v1 * v1;

endmodule
// cadence translate_on



 /// Non-Synthesizable Mag Module --- Complete, Don't Edit
//
// This is provided for reference.
//
module multi_step_seq
  ( output logic [31:0] result,
    output logic ready,
    input uwire [31:0] v0, v1,
    input uwire start,
    input uwire clk );

   localparam logic [2:0] rnd = 0; // 1 is round towards zero.

   uwire [7:0] mul_s, add_s;

   logic [2:0]  step;

   uwire [31:0] mul_a, mul_b;
   uwire [31:0] add_a, add_b;
   uwire [31:0] prod, sum;

   logic [31:0] ac0, ac1;

   localparam   int last_step = 4;

   always_ff @( posedge clk )
     if ( start ) step <= 0;
     else if ( step < last_step ) step <= step + 1;

   CW_fp_mult m1( .a(mul_a), .b(mul_b), .rnd(rnd), .z(prod), .status(mul_s));
   CW_fp_add  a1( .a(add_a), .b(add_b), .rnd(rnd), .z(sum),  .status(add_s));

   assign mul_a = step < 2  ? v0 : v1;
   assign mul_b = step == 0 ? v0 : v1;
   assign add_a = ac0,  add_b = ac1;

   always_ff @( posedge clk )
     begin

        ac0 <= prod;

        case ( step )
           0: ac1 <= 0;
           1: ac1 <= sum;
           2: ac1 <= sum;
        endcase

        if ( start ) ready <= 0; else if ( step == last_step-1 ) ready <= 1;

     end

   assign result = sum;

endmodule


//////////////////////////////////////////////////////////////////////////////
/// Testbench Code


// cadence translate_off

function automatic real rand_real(real minv, real maxv);
      rand_real = minv + ( maxv - minv ) * ( real'({$random}) ) / 2.0**32;
endfunction

function automatic shortreal fabs(shortreal val);
      fabs = val < 0 ? -val : val;
endfunction

program reactivate
   (output uwire clk_reactive, output int cycle_reactive,
    input uwire clk, input var int cycle);
   assign clk_reactive = clk;
   assign cycle_reactive = cycle;
endprogram


module testbench;

   typedef enum { MT_comb, MT_seq, MT_pipe } Module_Type;

   localparam int num_tests = 400;
   localparam int NUM_MUT = 4;
   localparam int err_limit = 7;
   localparam int trace_max_lines = 10;

   shortreal magr, vr[2];
   logic [31:0] vp[NUM_MUT][2];
   uwire [31:0] mag[NUM_MUT];

   uwire availn[NUM_MUT];
   logic avail[NUM_MUT];
   logic in_valid[NUM_MUT];

   typedef struct { int tidx; int cycle_start; int eta; } Test_Vector;

   typedef struct { int idx;
                    int err_count = 0;
                    int err_timing = 0;
                    Module_Type mt = MT_comb;
                    Test_Vector tests_active[$];
                    string trace_lines[$];
                    int eta_to_test[int];
                    bit all_tests_started = 0;
                    bit seq = 0; bit pipe = 0;
                    bit bpipe = 0;
                    int ncyc = 0;
                    int ncompleted = 0;
                    int cyc_tot = 0;
                    int latency = 0;
                    } Info;
   Info pi[string];

   localparam int cycle_limit = num_tests * 10;
   int cycle;
   bit done;
   logic clock;

   logic clk_reactive;
   int cycle_reactive;
   reactivate ra(clk_reactive,cycle_reactive,clock,cycle);

   initial begin
      clock = 0;
      cycle = 0;

      fork
         forever #10 cycle += ++clock;
         wait( done );
         wait( cycle >= cycle_limit )
           $write("*** Cycle limit exceeded, ending.\n");
      join_any;

      $finish();
   end

   task pi_seq(input int idx, input string name);
      automatic string m = $sformatf("%s", name);
      pi[m].idx = idx; pi[m].mt = MT_seq;
      pi[m].seq = 1; pi[m].bpipe = 0; pi[m].pipe = 0;
   endtask

   task pi_pipe(input int idx, input string name, input int ncyc);
      automatic string m = $sformatf("%s", name);
      pi[m].idx = idx; pi[m].mt = MT_pipe;
      pi[m].ncyc = ncyc;
      pi[m].seq = 1; pi[m].pipe = 1; pi[m].bpipe = 0;
   endtask


   multi_step_pipe m3( mag[3], availn[3], vp[3][0],vp[3][1], in_valid[3], clock );
   initial begin pi_pipe(3,"MS Pipe",m3.nstages); end

`ifdef xxx
   multi_step_pipe_sol m4( mag[4], availn[4], vp[4][0],vp[4][1], in_valid[4], clock );
   initial begin pi_pipe(4,"MS P Sol",m4.nstages); end
`endif

   always @*
     foreach ( availn[i] ) if ( availn[i] !== 1'bz ) avail[i] = availn[i];

   initial begin

      automatic int awaiting = pi.size();

      logic [31:0] vs[num_tests][2];
      shortreal vrs[num_tests][2];

      done = 0;

      foreach ( pi[mut] ) begin
         automatic int midx = pi[mut].idx;
         automatic int steps = pi[mut].ncyc;
         automatic int latency =
           !pi[mut].seq ? 1 : !pi[mut].pipe ? 2 * steps : steps;
         pi[mut].latency = latency;
         in_valid[midx] = 0;
      end

      for ( int i=0; i<num_tests; i++ ) begin

         if ( i < 4 ) begin

            // In first eight tests vector components are zero or one.
            //
            for ( int j=0; j<2; j++ ) vrs[i][j] = i & 1 << j ? 1.0 : 0.0;

         end else begin

            // In other tests vector components are randomly chosen.
            //
            for ( int j=0; j<2; j++ ) vrs[i][j] = rand_real(-10,+10);

         end

         for ( int j=0; j<2; j++ ) vs[i][j] = $shortrealtobits(vrs[i][j]);

      end

      fork forever @( negedge clk_reactive ) foreach ( pi[mut] ) begin
         automatic int midx = pi[mut].idx;
         if ( !in_valid[midx] && pi[mut].pipe ) begin
            vp[midx][0] = cycle;
            vp[midx][1] = 1;
         end
      end join_none;

      repeat ( 2 * 10 ) @( negedge clock );

      foreach ( pi[mutii] ) begin
         automatic string muti = mutii;

         fork begin
            automatic string mut = muti;
            automatic int midx = pi[mut].idx;
            for ( int i=0; i<num_tests; i++ ) begin
               automatic int gap_cyc =
                 ( {$random} % 2 ) ? {$random} % ( 5 ) : 0;
               automatic Test_Vector tv;
               repeat ( gap_cyc ) @( negedge clock );
               vp[midx] = vs[i];
               in_valid[midx] = 1;
               tv.tidx = i;
               tv.cycle_start = cycle;
               tv.eta = tv.cycle_start + pi[mut].latency;
               pi[mut].eta_to_test[tv.eta] = i;
               pi[mut].tests_active.push_back( tv );
               @( negedge clock );
               in_valid[midx] = 0;
            end
            pi[mut].all_tests_started = 1;
         end join_none;

         fork begin
            automatic string mut = muti;
            automatic int midx = pi[mut].idx;
            automatic int n_timing_errs = 0;
            automatic int n_correct_val = 0; // Reset when test over.
            while ( !pi[mut].all_tests_started || pi[mut].tests_active.size() )
              @( negedge clk_reactive ) begin
                 automatic shortreal v0 = $bitstoshortreal(vp[midx][0]);
                 automatic shortreal v1 = $bitstoshortreal(vp[midx][1]);
                 automatic shortreal r_future = v0*v0+v0*v1+v1*v1;
                 automatic shortreal r = $bitstoshortreal(mag[midx]);
                 automatic Test_Vector tv = pi[mut].tests_active[0];
                 automatic bit avail_sh = pi[mut].eta_to_test.exists(cycle);
                 automatic int ita = tv.tidx;
                 automatic int ieta =
                   avail_sh ? pi[mut].eta_to_test[cycle] : -1;
                 automatic int i = ita > ieta ? ita : ieta;
                 automatic shortreal v0p = vrs[i][0], v1p = vrs[i][1];
                 automatic shortreal shadow_magr = v0p*v0p+v0p*v1p+v1p*v1p;
                 automatic string in_txt = in_valid[midx]
                   ? $sformatf("In: %5.1f,%5.1f -> %5.1f", v0, v1, r_future)
                   : "start=0";
                 automatic shortreal err_mag = fabs( r - shadow_magr );
                 automatic bit okay = err_mag < 1e-4;
                 automatic bit err_rdy = avail_sh !== avail[midx];
                 automatic bit err_val = avail_sh && !okay;
                 automatic string tr_txt =
                   $sformatf
                     ("%-8s Cyc %3d  %-24s  Rdy %1d%s, Res: %5.1f %0s\n",
                      mut, cycle, in_txt,
                      avail[midx],
                      err_rdy ? "X" : " ",
                      r,
                      okay &&  avail[midx] && avail_sh  ? "Good" :
                      okay && !avail[midx] && avail_sh  ? "XX: Need Rdy" :
                      okay && avail[midx] && !avail_sh ? "XX: Early" :
                      !okay && avail_sh ? "XX: Wrong" :
                      avail[midx] && !avail_sh ? "XX: Unexpected" : ""
                      );

                 if ( err_rdy ) n_timing_errs++;
                 if ( okay ) n_correct_val++;

                 if ( pi[mut].ncompleted < 3 )
                   $write("%s",tr_txt);
                 else
                   pi[mut].trace_lines.push_back( tr_txt );

                 if ( pi[mut].err_count < err_limit
                      && pi[mut].err_timing < err_limit
                      && ( err_rdy || err_val ) )
                   while ( pi[mut].trace_lines.size() )
                     $write("%s", pi[mut].trace_lines.pop_front() );

                 if ( avail_sh ) begin
                    pi[mut].tests_active.delete(0);
                    pi[mut].ncompleted++;

                    if ( n_timing_errs ) begin
                       pi[mut].err_timing++;
                       n_timing_errs = 0;
                    end

                    if ( n_correct_val == 0 ) begin
                       pi[mut].err_count++;
                       if ( pi[mut].err_count <= err_limit ) begin
                          $write
                            ("%-8s test %0d: Inputs at cyc %0d, result expected at cyc %0d. Wrong val: h'%8h  %7.4f != %7.4f (correct)\n",
                             mut, i, tv.cycle_start, tv.eta,
                             mag[midx], r, shadow_magr);
                       end
                    end
                    n_correct_val = 0;
                 end

                 if ( pi[mut].trace_lines.size() > trace_max_lines )
                   pi[mut].trace_lines.delete(0);
              end
            awaiting--;
         end join_none
      end

      wait( awaiting == 0 || cycle > cycle_limit );

      foreach ( pi[ mut ] )
        $write("For %0s ran %0d tests: Errors: %0d wrong val, %0d bad timing\n",
               mut, num_tests,
               pi[mut].err_count, pi[mut].err_timing);


      done = 1;

      $finish(2);

   end

endmodule


// cadence translate_on

`default_nettype wire

`include "/apps/linux/cadence/GENUS211/share/synth/lib/chipware/sim/verilog/CW/CW_fp_mult.v"
`include "/apps/linux/cadence/GENUS211/share/synth/lib/chipware/sim/verilog/CW/CW_fp_add.v"
