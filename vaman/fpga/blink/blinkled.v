module blinkled (
    output wire redled,
    output wire greenled,
    output wire blueled
);
    
    wire clk;
    integer delay;
    reg	led;

    qlal4s3b_cell_macro u_qlal4s3b_cell_macro (
        .Sys_Clk0 (clk),
    );

    always@(posedge clk) 
    begin
        delay = delay+1;
        if(delay > 20000000)
        begin
            delay=0;
            led=!led;
        end
    end
    assign greenled = led;
endmodule
