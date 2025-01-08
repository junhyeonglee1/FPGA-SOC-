
`timescale 1 ns / 1 ps

	module rtc_all_v1_0 #
	(
		// Users to add parameters here

		// User parameters ends
		// Do not modify the parameters beyond this line


		// Parameters of Axi Slave Bus Interface S00_AXI
		parameter integer C_S00_AXI_DATA_WIDTH	= 32,
		parameter integer C_S00_AXI_ADDR_WIDTH	= 6
	)
	(
		// Users to add ports here

		// User ports ends
		// Do not modify the ports beyond this line


		// Ports of Axi Slave Bus Interface S00_AXI
		input wire  s00_axi_aclk,
		input wire  s00_axi_aresetn,
		input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_awaddr,
		input wire [2 : 0] s00_axi_awprot,
		input wire  s00_axi_awvalid,
		output wire  s00_axi_awready,
		input wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_wdata,
		input wire [(C_S00_AXI_DATA_WIDTH/8)-1 : 0] s00_axi_wstrb,
		input wire  s00_axi_wvalid,
		output wire  s00_axi_wready,
		output wire [1 : 0] s00_axi_bresp,
		output wire  s00_axi_bvalid,
		input wire  s00_axi_bready,
		input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_araddr,
		input wire [2 : 0] s00_axi_arprot,
		input wire  s00_axi_arvalid,
		output wire  s00_axi_arready,
		output wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_rdata,
		output wire [1 : 0] s00_axi_rresp,
		output wire  s00_axi_rvalid,
		input wire  s00_axi_rready
	);

	wire        wr;
	wire [25:0] initialvalue; 
	wire [5:0]  secPort;
	wire [5:0]  minPort;
	wire [4:0]  hourPort;
	wire [4:0]  dayPort;
	wire [3:0]  monthPort;
// Instantiation of Axi Bus Interface S00_AXI
	rtc_all_v1_0_S00_AXI # ( 
		.C_S_AXI_DATA_WIDTH(C_S00_AXI_DATA_WIDTH),
		.C_S_AXI_ADDR_WIDTH(C_S00_AXI_ADDR_WIDTH)
	) rtc_all_v1_0_S00_AXI_inst (
		.S_AXI_ACLK(s00_axi_aclk),
		.S_AXI_ARESETN(s00_axi_aresetn),
		.S_AXI_AWADDR(s00_axi_awaddr),
		.S_AXI_AWPROT(s00_axi_awprot),
		.S_AXI_AWVALID(s00_axi_awvalid),
		.S_AXI_AWREADY(s00_axi_awready),
		.S_AXI_WDATA(s00_axi_wdata),
		.S_AXI_WSTRB(s00_axi_wstrb),
		.S_AXI_WVALID(s00_axi_wvalid),
		.S_AXI_WREADY(s00_axi_wready),
		.S_AXI_BRESP(s00_axi_bresp),
		.S_AXI_BVALID(s00_axi_bvalid),
		.S_AXI_BREADY(s00_axi_bready),
		.S_AXI_ARADDR(s00_axi_araddr),
		.S_AXI_ARPROT(s00_axi_arprot),
		.S_AXI_ARVALID(s00_axi_arvalid),
		.S_AXI_ARREADY(s00_axi_arready),
		.S_AXI_RDATA(s00_axi_rdata),
		.S_AXI_RRESP(s00_axi_rresp),
		.S_AXI_RVALID(s00_axi_rvalid),
		.S_AXI_RREADY(s00_axi_rready),
		.wr(wr),
		.initialvalue(initialvalue),
		.secPort(secPort),
    	.minPort(minPort),
    	.hourPort(hourPort),
    	.dayPort(dayPort),
    	.monthPort(monthPort)
	);

// Add user logic here
	rtc_upcounter U_rtc_upcounter (
    .clk(s00_axi_aclk),
    .reset(s00_axi_aresetn),
    .wr(wr),
    .initialvalue(initialvalue),
    .o_sec(secPort),
    .o_min(minPort),
    .o_hour(hourPort),
    .o_day(dayPort),
    .o_month(monthPort)
);
	

	// Add user logic here

	// User logic ends

	endmodule

module rtc_upcounter (
    input clk,
    input reset,
    input wr,
    input [25:0] initialvalue,
    output [5:0] o_sec,
    output [5:0] o_min,
    output [4:0] o_hour,
    output [4:0] o_day,
    output [3:0] o_month
);

    wire w_clk_sec;
    wire w_tick_sec, w_tick_min, w_tick_hour, w_tick_day;

    // Clock division for 1 second tick
    clkdiv_sec U_clkdiv_sec (
        .clk  (clk),
        .reset(reset),
        .o_clk(w_clk_sec)
    );

    // Second counter
    counter_sec U_counter_sec (
        .clk(clk),
        .clk_sec(w_clk_sec),
        .reset(reset),
        .wr(wr),
        .initialvalue(initialvalue),
        .o_tick_sec(w_tick_sec),
        .o_sec(o_sec)
    );

    // Minute counter
    counter_min U_counter_min (
        .clk(clk),
        .reset(reset),
        .i_tick_min(w_tick_sec),
        .wr(wr),
        .initialvalue(initialvalue),
        .o_tick_min(w_tick_min),
        .o_min(o_min)
    );

    // Hour counter
    counter_hour U_counter_hour (
        .clk(clk),
        .reset(reset),
        .i_tick_hour(w_tick_min),
        .wr(wr),
        .initialvalue(initialvalue),
        .o_tick_hour(w_tick_hour),
        .o_hour(o_hour)
    );

    // Day counter
    counter_day U_counter_day (
        .clk(clk),
        .reset(reset),
        .i_tick_day(w_tick_hour),
        .wr(wr),
        .initialvalue(initialvalue),
        .o_tick_day(w_tick_day),
        .o_day(o_day)
    );

    // Month counter
    counter_month U_counter_month (
        .clk(clk),
        .reset(reset),
        .i_tick_month(w_tick_day),
        .wr(wr),
        .initialvalue(initialvalue),
        .o_month(o_month)
    );

endmodule


// counter_sec module
module counter_sec (
    input             clk,
    input             clk_sec,
    input             reset,
    input             wr,
    input      [25:0] initialvalue,
    output reg        o_tick_sec,
    output     [ 5:0] o_sec
);

    reg [5:0] r_counter;
    assign o_sec = r_counter;

    always @(posedge clk, negedge reset) begin
        if (!reset) begin
            r_counter  <= 0;
            o_tick_sec <= 0;
        end else begin
            if (clk_sec) begin
                if (r_counter == 59) begin
                    r_counter  <= 0;
                    o_tick_sec <= 1;
                end else begin
                    r_counter <= r_counter + 1;
                end
            end else if (wr) begin
                r_counter <= initialvalue[5:0];
            end else begin
                o_tick_sec <= 0;
            end
        end
    end
endmodule

// counter_min module
module counter_min (
    input             clk,
    input             reset,
    input             i_tick_min,
    input             wr,
    input      [25:0] initialvalue,
    output reg        o_tick_min,
    output     [ 5:0] o_min
);

    reg [5:0] r_counter;
    assign o_min = r_counter;

    always @(posedge clk, negedge reset) begin
        if (!reset) begin
            r_counter  <= 0;
            o_tick_min <= 0;
        end else begin
            if (i_tick_min) begin
                 if (r_counter == 59) begin
                    r_counter  <= 0;
                    o_tick_min <= 1;
                end else begin
                    r_counter <= r_counter + 1;
                end
            end 
            else if (wr) begin
               r_counter <= initialvalue[11:6];
            end else begin
                o_tick_min <= 0;
            end
        end
    end
endmodule

// counter_hour module
module counter_hour (
    input             clk,
    input             reset,
    input             i_tick_hour,
    input             wr,
    input      [25:0] initialvalue,
    output reg        o_tick_hour,
    output     [ 4:0] o_hour
);

    reg [5:0] r_counter;
    assign o_hour = r_counter;

    always @(posedge clk, negedge reset) begin
        if (!reset) begin
            r_counter   <= 0;
            o_tick_hour <= 0;
        end else begin
            if (i_tick_hour) begin
                 if (r_counter == 23) begin
                    r_counter   <= 0;
                    o_tick_hour <= 1;
                end else begin
                    r_counter <= r_counter + 1;
                end
            end else if (wr) begin
                r_counter <= initialvalue[16:12];
            end else begin
                o_tick_hour <= 0;
            end
        end
    end
endmodule

// counter_day module
module counter_day (
    input             clk,
    input             reset,
    input             i_tick_day,
    input             wr,
    input      [25:0] initialvalue,
    output reg        o_tick_day,
    output     [ 4:0] o_day
);

    reg [5:0] r_counter;
    assign o_day = r_counter;

    always @(posedge clk, negedge reset) begin
        if (!reset) begin
            r_counter  <= 0;
            o_tick_day <= 0;
        end else begin
            if (i_tick_day) begin
                if (r_counter == 30) begin
                    r_counter  <= 0;
                    o_tick_day <= 1;
                end else begin
                    r_counter <= r_counter + 1;
                end
            end else if (wr) begin
                r_counter <= initialvalue[21:17];
            end else begin
                o_tick_day <= 0;
            end
        end
    end
endmodule

// counter_month module
module counter_month (
    input         clk,
    input         reset,
    input         i_tick_month,
    input         wr,
    input  [25:0] initialvalue,
    output [ 3:0] o_month
);

    reg [5:0] r_counter;
    assign o_month = r_counter;

    always @(posedge clk, negedge reset) begin
        if (!reset) begin
            r_counter <= 0;
        end else begin
            if (i_tick_month) begin
                if (r_counter == 11) begin
                    r_counter <= 0;
                end else begin
                    r_counter <= r_counter + 1;
                end
            end else if (wr) begin
                r_counter <= initialvalue[25:22];
            end else begin 
                r_counter <= r_counter;
            end
        end
    end
endmodule

// clkdiv_sec module
module clkdiv_sec (
    input  clk,
    input  reset,
    output o_clk
);

    reg [26:0] r_counter;
    reg r_clk;

    assign o_clk = r_clk;

    always @(posedge clk, negedge reset) begin
        if (!reset) begin
            r_counter <= 0;
            r_clk <= 1'b0;
        end else begin
            if (r_counter == 100_000_000 - 1) begin
                r_counter <= 0;
                r_clk <= 1'b1;
            end else begin
                r_counter <= r_counter + 1;
                r_clk <= 1'b0;
            end
        end
    end
endmodule