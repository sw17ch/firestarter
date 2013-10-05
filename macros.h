#ifndef MACROS_H
#define MACROS_H

#define IGNORE(V) (void)(V)
#define IX(X,Y,WIDTH) ((X) + ((WIDTH) * (Y)))

#define DIR_IX_NW(X,Y,WIDTH) IX((X) - 1, (Y) - 1, (WIDTH))
#define DIR_IX_N(X,Y,WIDTH)  IX((X)    , (Y) - 1, (WIDTH))
#define DIR_IX_NE(X,Y,WIDTH) IX((X) + 1, (Y) - 1, (WIDTH))

#define DIR_IX_W(X,Y,WIDTH)  IX((X) - 1, (Y)    , (WIDTH))
#define DIR_IX_E(X,Y,WIDTH)  IX((X) + 1, (Y)    , (WIDTH))

#define DIR_IX_SW(X,Y,WIDTH) IX((X) - 1, (Y) + 1, (WIDTH))
#define DIR_IX_S(X,Y,WIDTH)  IX((X)    , (Y) + 1, (WIDTH))
#define DIR_IX_SE(X,Y,WIDTH) IX((X) + 1, (Y) + 1, (WIDTH))

#define ONE_IF_EQ(T,E) ((T) == (E) ? 1 : 0)

#endif /* MACROS_H */
