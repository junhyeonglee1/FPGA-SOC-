
`timescale 1 ns / 1 ps

module I2C_Master_controller_v1_0 #(
    // Users to add parameters here

    // User parameters ends
    // Do not modify the parameters beyond this line


    // Parameters of Axi Slave Bus Interface S00_AXI
    parameter integer C_S00_AXI_DATA_WIDTH = 32,
    parameter integer C_S00_AXI_ADDR_WIDTH = 7
) (
    // Users to add ports here
    inout  sda,
    output sclk,
    // User ports ends
    // Do not modify the ports beyond this line


    // Ports of Axi Slave Bus Interface S00_AXI
    input wire s00_axi_aclk,
    input wire s00_axi_aresetn,
    input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_awaddr,
    input wire [2 : 0] s00_axi_awprot,
    input wire s00_axi_awvalid,
    output wire s00_axi_awready,
    input wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_wdata,
    input wire [(C_S00_AXI_DATA_WIDTH/8)-1 : 0] s00_axi_wstrb,
    input wire s00_axi_wvalid,
    output wire s00_axi_wready,
    output wire [1 : 0] s00_axi_bresp,
    output wire s00_axi_bvalid,
    input wire s00_axi_bready,
    input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_araddr,
    input wire [2 : 0] s00_axi_arprot,
    input wire s00_axi_arvalid,
    output wire s00_axi_arready,
    output wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_rdata,
    output wire [1 : 0] s00_axi_rresp,
    output wire s00_axi_rvalid,
    input wire s00_axi_rready
);

    wire        start;
    wire [ 7:0] byte_count;
    wire [10:0] prescale;
    wire        rw;
    wire [ 6:0] addr;
    wire [ 7:0] wdata_0;
    wire [ 7:0] wdata_1;
    wire [ 7:0] wdata_2;
    wire [ 7:0] wdata_3;
    wire [ 7:0] wdata_4;
    wire [ 7:0] wdata_5;
    wire [ 7:0] wdata_6;
    wire [ 7:0] wdata_7;
    wire [ 7:0] wdata_8;
    wire [ 7:0] wdata_9;
    wire [ 7:0] wdata_10;
    wire [ 7:0] wdata_11;
    // wire [ 7:0] rdata;


    wire        sclk_tick;
    wire        sclk_en;
    wire        i2c_done;
    // Instantiation of Axi Bus Interface S00_AXI
    I2C_Master_controller_v1_0_S00_AXI #(
        .C_S_AXI_DATA_WIDTH(C_S00_AXI_DATA_WIDTH),
        .C_S_AXI_ADDR_WIDTH(C_S00_AXI_ADDR_WIDTH)
    ) I2C_Master_controller_v1_0_S00_AXI_inst (
        .S_AXI_ACLK   (s00_axi_aclk),
        .S_AXI_ARESETN(s00_axi_aresetn),
        .S_AXI_AWADDR (s00_axi_awaddr),
        .S_AXI_AWPROT (s00_axi_awprot),
        .S_AXI_AWVALID(s00_axi_awvalid),
        .S_AXI_AWREADY(s00_axi_awready),
        .S_AXI_WDATA  (s00_axi_wdata),
        .S_AXI_WSTRB  (s00_axi_wstrb),
        .S_AXI_WVALID (s00_axi_wvalid),
        .S_AXI_WREADY (s00_axi_wready),
        .S_AXI_BRESP  (s00_axi_bresp),
        .S_AXI_BVALID (s00_axi_bvalid),
        .S_AXI_BREADY (s00_axi_bready),
        .S_AXI_ARADDR (s00_axi_araddr),
        .S_AXI_ARPROT (s00_axi_arprot),
        .S_AXI_ARVALID(s00_axi_arvalid),
        .S_AXI_ARREADY(s00_axi_arready),
        .S_AXI_RDATA  (s00_axi_rdata),
        .S_AXI_RRESP  (s00_axi_rresp),
        .S_AXI_RVALID (s00_axi_rvalid),
        .S_AXI_RREADY (s00_axi_rready),
        .start        (start),
        .rw           (rw),
        .addr         (addr),
        .wdata_0      (wdata_0),
        .wdata_1      (wdata_1),
        .wdata_2      (wdata_2),
        .wdata_3      (wdata_3),
        .wdata_4      (wdata_4),
        .wdata_5      (wdata_5),
        .wdata_6      (wdata_6),
        .wdata_7      (wdata_7),
        .wdata_8      (wdata_8),
        .wdata_9      (wdata_9),
        .wdata_10     (wdata_10),
        .wdata_11     (wdata_11),
        .sclk_prescale(prescale),
        .byte_count   (byte_count),
        .i2c_done     (i2c_done)
    );

    wire sclk_half_en, sclk_half_tick;
    // Add user logic here
    I2C_FSM u_I2C_FSM (
        .clk           (s00_axi_aclk),
        .rstn          (s00_axi_aresetn),
        .sclk_tick     (sclk_tick),
        .rw            (rw),
        .addr          (addr),
        .wdata_0       (wdata_0),
        .wdata_1       (wdata_1),
        .wdata_2       (wdata_2),
        .wdata_3       (wdata_3),
        .wdata_4       (wdata_4),
        .wdata_5       (wdata_5),
        .wdata_6       (wdata_6),
        .wdata_7       (wdata_7),
        .wdata_8       (wdata_8),
        .wdata_9       (wdata_9),
        .wdata_10      (wdata_10),
        .wdata_11      (wdata_11),
        .byte_count    (byte_count),
        // .rdata     (rdata),
        .sda           (sda),
        .start         (start),
        .sclk_out      (sclk),
        .sclk_en       (sclk_en),
        .sclk_half_en  (sclk_half_en),
        .sclk_half_tick(sclk_half_tick),
        .i2c_done      (i2c_done)
    );

    sclk_div u_i2c_clk (
        .clk          (s00_axi_aclk),
        .rstn         (s00_axi_aresetn),
        .sclk_prescale(prescale),
        .sclk_tick    (sclk_tick),
        .en           (sclk_en)
    );

    sclk_div u_i2c_clk_forhalftick (
        .clk          (s00_axi_aclk),
        .rstn         (s00_axi_aresetn),
        .sclk_prescale(prescale * 2),
        .sclk_tick    (sclk_half_tick),
        .en           (sclk_half_en)
    );


    // User logic ends

endmodule

module I2C_FSM (
    input        clk,
    input        rstn,
    input        sclk_tick,
    input        rw,
    input  [6:0] addr,
    input  [7:0] wdata_0,
    input  [7:0] wdata_1,
    input  [7:0] wdata_2,
    input  [7:0] wdata_3,
    input  [7:0] wdata_4,
    input  [7:0] wdata_5,
    input  [7:0] wdata_6,
    input  [7:0] wdata_7,
    input  [7:0] wdata_8,
    input  [7:0] wdata_9,
    input  [7:0] wdata_10,
    input  [7:0] wdata_11,
    input  [7:0] wdata_12,
    input  [7:0] wdata_13,
    input  [7:0] wdata_14,
    input  [7:0] wdata_15,
    input  [7:0] wdata_16,
    input  [7:0] byte_count,
    output [7:0] rdata,
    inout        sda,
    input        start,
    output       sclk_out,
    output       sclk_en,
    input        sclk_half_tick,
    output       sclk_half_en,
    output       i2c_done
);

    //reg [7:0] wdata_mem[31:0];

    reg [7:0] wdata_memory[0:31];

    always @(*) begin
        wdata_memory[0]  = wdata_0;
        wdata_memory[1]  = wdata_1;
        wdata_memory[2]  = wdata_2;
        wdata_memory[3]  = wdata_3;
        wdata_memory[4]  = wdata_4;
        wdata_memory[5]  = wdata_5;
        wdata_memory[6]  = wdata_6;
        wdata_memory[7]  = wdata_7;
        wdata_memory[8]  = wdata_8;
        wdata_memory[9]  = wdata_9;
        wdata_memory[10] = wdata_10;
        wdata_memory[11] = wdata_11;
        wdata_memory[12] = wdata_12;
        wdata_memory[13] = wdata_13;
        wdata_memory[14] = wdata_14;
        wdata_memory[15] = wdata_15;
    end


    localparam S_IDLE = 4'b0000, S_START = 4'b0001, S_ADDR = 4'b0010, S_ACK_ADDR = 4'b0011, S_WDATA = 4'b0100, S_RDATA = 4'b0101, S_ACK_WDATA = 4'b0110, S_RE_START = 4'b1000, S_ACK_RDATA = 4'b0111, S_STOP = 4'b1001;
    localparam SCLK_OFF = 1'b0, SCLK_ON = 1'b1;

    reg [3:0] curr_state, next_state;
    reg sclk_state, sclk_state_next;
    reg sda_reg, sda_reg_next;
    reg inout_reg, inout_reg_next;

    reg en_sclk_reg, en_sclk_reg_next;
    reg [2:0] bit_cnt_reg, bit_cnt_next;
    reg [6:0] temp_addr_reg, temp_addr_next;
    reg [7:0] temp_wdata_reg, temp_wdata_next;
    reg [7:0] byte_cnt_reg, byte_cnt_next;
    reg i2c_done_reg, i2c_done_next;

    wire w_sda_reg = sda_reg;
    wire w_inout_sig = inout_reg;

    reg sclk_reg, sclk_reg_next;

    assign sclk_en  = en_sclk_reg;
    assign i2c_done = i2c_done_reg;
    // sda input mode signal
    reg sda_input_signal;
    reg sclk_half_en_reg;

    assign sclk_half_en = sclk_half_en_reg;
    always @(posedge clk, negedge rstn) begin
        if (!rstn) begin
            sda_input_signal <= 0;
        end else begin
            sda_input_signal <= sda;
        end
    end

    assign sda = (w_inout_sig) ? sda_reg : 1'bz;
    //assign sclk_out = (en_sclk_reg) ? sclk_tick : 1'b1;
    assign sclk_out = sclk_tick;

    reg sclk_0, sclk_1;
    wire sclk_redge, sclk_fedge;

    //sclk edge detect	
    always @(posedge clk, negedge rstn) begin
        if (!rstn) begin
            sclk_0 <= 0;
            sclk_1 <= 0;
        end
        sclk_0 <= sclk_reg;
        sclk_1 <= sclk_0;
    end



    assign sclk_redge = sclk_0 & ~sclk_1;
    assign sclk_fedge = ~sclk_0 & sclk_1;

    reg sclk_half0, sclk_half1;
    wire sclk_halfredge, sclk_halffedge;

    always @(posedge clk, negedge rstn) begin
        if (!rstn) begin
            sclk_half0 <= 0;
            sclk_half1 <= 0;
        end
        sclk_half0 <= sclk_half_tick;
        sclk_half1 <= sclk_half0;
    end

    assign sclk_halfredge = sclk_half0 & ~sclk_half1;
    assign sclk_halffedge = ~sclk_half0 & sclk_half1;

    //state register
    always @(posedge clk, negedge rstn) begin
        if (!rstn) begin
            curr_state     <= S_IDLE;
            sclk_state     <= SCLK_OFF;
            sda_reg        <= 1;
            inout_reg      <= 0;
            sclk_reg       <= 0;
            en_sclk_reg    <= 0;
            bit_cnt_reg    <= 0;
            temp_addr_reg  <= 0;
            temp_wdata_reg <= 0;
            byte_cnt_reg   <= 0;
            i2c_done_reg   <= 0;
        end else begin
            curr_state     <= next_state;
            sclk_state     <= sclk_state_next;
            sda_reg        <= sda_reg_next;
            inout_reg      <= inout_reg_next;
            sclk_reg       <= sclk_tick;
            en_sclk_reg    <= en_sclk_reg_next;
            bit_cnt_reg    <= bit_cnt_next;
            temp_addr_reg  <= temp_addr_next;
            temp_wdata_reg <= temp_wdata_next;
            byte_cnt_reg   <= byte_cnt_next;
            i2c_done_reg   <= i2c_done_next;
        end
    end

    //next state combinational logic for SDA 
    always @(*) begin
        next_state = curr_state;
        sda_reg_next = sda_reg;
        inout_reg_next = inout_reg;
        bit_cnt_next = bit_cnt_reg;
        temp_addr_next = temp_addr_reg;
        temp_wdata_next = temp_wdata_reg;
        byte_cnt_next = byte_cnt_reg;
        i2c_done_next = i2c_done_reg;
        case (curr_state)
            S_IDLE: begin
                i2c_done_next  = 1'b0;
                inout_reg_next = 1'b1;
                sda_reg_next   = 1'b1;
                if (start) begin
                    next_state = S_START;
                end
            end
            S_START: begin
                inout_reg_next = 1'b1;
                sda_reg_next   = 1'b0;
                if (sclk_fedge) begin
                    next_state = S_ADDR;
                    temp_addr_next = addr;
                    bit_cnt_next = 0;
                end
            end
            S_ADDR: begin
                inout_reg_next = 1'b1;
                sda_reg_next   = temp_addr_reg[6];
                if (sclk_fedge) begin
                    if (bit_cnt_reg == 7) begin
                        next_state   = S_ACK_ADDR;
                        bit_cnt_next = 0;
                    end else if (bit_cnt_reg == 6) begin
                        temp_addr_next = rw;
                        bit_cnt_next   = bit_cnt_reg + 1;
                    end else begin
                        temp_addr_next = {temp_addr_reg[5:0], 1'b0};
                        bit_cnt_next   = bit_cnt_reg + 1;
                    end
                end
            end
            S_ACK_ADDR: begin
                inout_reg_next = 1'b0;
                if (sclk_fedge) begin
                    if (sda_input_signal == 0) begin
                        if (rw == 0) begin
                            next_state = S_WDATA;
                            temp_wdata_next = wdata_memory[0];
                            byte_cnt_next = byte_count;
                            bit_cnt_next = 0;
                        end else begin
                            next_state = S_RDATA;
                        end
                    end else begin
                        next_state = S_STOP;
                    end
                end
            end
            S_WDATA: begin
                inout_reg_next = 1'b1;
                sda_reg_next   = temp_wdata_reg[7];
                if (sclk_fedge) begin
                    if (bit_cnt_reg == 7) begin
                        next_state = S_ACK_WDATA;
                        byte_cnt_next = byte_cnt_reg - 1;
                        bit_cnt_next = 0;
                    end else begin
                        temp_wdata_next = {temp_wdata_reg[6:0], 1'b0};
                        bit_cnt_next = bit_cnt_reg + 1;
                    end
                end
            end
            S_ACK_WDATA: begin
                inout_reg_next = 1'b0;
                if (sclk_redge) begin
                    if (sda_input_signal == 0) begin
                        if (byte_cnt_reg == 0) begin
                            temp_wdata_next = wdata_memory[byte_cnt_reg];
                            next_state = S_WDATA;
                        end else begin
                            next_state = S_STOP;
                        end
                    end else begin
                        next_state = S_STOP;
                    end
                end
            end
            S_RDATA: begin
            end
            S_ACK_RDATA: begin
            end
            S_RE_START: begin  //not use;
                inout_reg_next = 1'b1;
                sda_reg_next = 1'b1;
                temp_wdata_next = wdata_memory[byte_cnt_reg];
                next_state = S_WDATA;
            end
            S_STOP: begin
                inout_reg_next = 1'b1;
                sda_reg_next   = 1'b1;
                    i2c_done_next = 1'b1;
                    next_state = S_IDLE;
            end
        endcase
    end


    //next state combinational logic for SCLK
    always @(*) begin
        sclk_state_next  = sclk_state;
        en_sclk_reg_next = en_sclk_reg;
        case (sclk_state)
            SCLK_OFF: begin
                if (sda_reg == 1'b0) begin
                    sclk_half_en_reg = 1'b1;
                    if (sclk_halfredge) sclk_state_next = SCLK_ON;
                end else begin
                    en_sclk_reg_next = 1'b0;
                    sclk_half_en_reg = 1'b0;
                end
            end
            SCLK_ON: begin
                en_sclk_reg_next = 1'b1;
                if (curr_state == S_STOP) begin
                    sclk_state_next = SCLK_OFF;
                end
            end
        endcase
    end

endmodule
module sclk_div (
    input clk,
    input rstn,
    input [10:0] sclk_prescale,
    output sclk_tick,
    input en
);

    reg [11:0] div_counter;
    reg div_clk;
    wire [18:0] prescale;

    assign prescale  = 100_000_000 / (sclk_prescale * 1000);
    assign sclk_tick = div_clk;

    always @(posedge clk, negedge rstn) begin
        if (!rstn) begin
            div_counter <= 0;
            div_clk <= 0;
        end else begin
            if (en) begin
                if (div_counter == prescale - 1) begin
                    //if (div_counter == 10) begin  //for simul
                    div_counter <= 0;
                    div_clk <= 1;
                end else if (div_counter <= prescale / 2 - 1) begin
                    div_counter <= div_counter + 1;
                    div_clk <= 0;
                end else begin
                    div_counter <= div_counter + 1;
                    div_clk <= 1;
                end
            end else begin
                div_clk <= 1;
                div_counter <= 0;
            end
        end
    end

endmodule
