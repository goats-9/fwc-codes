module inc_enc (
    input [3:0] digit,
    output [6:0] sevenseg,
);
    assign sevenseg[6] = (!digit[3] && !digit[2] && !digit[1] && !digit[0]) || (!digit[2] && digit[1] && digit[0]);
    assign sevenseg[5] = digit[2] && !digit[1];
    assign sevenseg[4] = (!digit[3] && !digit[2] && !digit[1] && digit[0]);
    assign sevenseg[3] = sevenseg[6] || (digit[2] && digit[1] && !digit[0]);
    assign sevenseg[2] = (!digit[2] || !digit[0]) && (digit[1] || !digit[0]);
    assign sevenseg[1] = (!digit[3] && !digit[2] && !digit[1]) || (digit[1] && !digit[0]);
    assign sevenseg[0] = (!digit[3] && !digit[2] && !digit[1] && !digit[0]) || (digit[2] && digit[1] && !digit[0]) || (digit[3] && digit[0]);
endmodule
