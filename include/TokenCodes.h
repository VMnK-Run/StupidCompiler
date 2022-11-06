enum TokenCode{
    UNDIFNIE = 0,   //未定义

    /*KW 关键字*/
    KW_INT,         // int
    KW_VOID,        // void
    KW_RETURN,      // return
    KW_CONST,       // const
    KW_MAIN,        // main

    /*OP 运算符*/
    OP_PLUS,        // +
    OP_MINUS,       // -
    OP_MULTIPLY,    // *
    OP_DIVIDE,      // /
    OP_PERCENT,     // %
    OP_ASSIGN,      // =
    OP_GT,          // >
    OP_LT,          // <
    OP_EQUAL,       // ==
    OP_LEQ,         // <=
    OP_GEQ,         // >=
    OP_NEQ,         // !=
    OP_AND,         // &&
    OP_OR,          // ||

    /*SE 界符*/
    SE_LPARENT,     // (
    SE_RPARENT,     // )
    SE_LBRACES,     // { 
    SE_RBARCES,     // }
    SE_SEMICOLON,   // ;
    SE_COMMA,       // ,

    IDN,            // 标识符: (letter|_)(letter|digit|_)*
    INT             // 整数: digit digit*
};