
#if CPP_NOW
#define public
#else
namespace Enum_
{
#endif



    public enum CONSTANT
    {
        E_A = -2,
        E_B = -1,
        E_C,
        E_D,
        E_E,
    };


    public enum Enum1805171009
    {
        E_A = -2,
        E_B = -1,
        E_C,
        E_D,
        E_E,
    };


    public enum MyEnum2
    {
        MyEnum2Value1,
        MyEnum2Value2,
    };


    public enum MyEnum3
    {
        MyEnum3Value1,
        MyEnum3Value2,
    };


    public enum DoubleDataPool
    {
        DoubleDataPoolSize = 10000,
        DoubleDataPoolMinBoundary = 1,


        DoubleDataPoolMaxBoundary = DoubleDataPoolSize / 8,
    };

    public enum IntDataPool
    {
        IntDataPoolSize = 10000,
        IntDataPoolMinBoundary = 1,

        WakingMethod = 100,

        IntDataPoolMaxBoundary = IntDataPoolSize / 4,
    };




#if CPP_NOW
#undef public
#else
}
#endif