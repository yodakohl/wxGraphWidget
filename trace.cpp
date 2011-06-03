#include "trace.h"


void t_Trace::add_Data(float const &value)
{
    Data.push_back(value);
    if (Data.size() > max_values)
    {
        Data.pop_front();
    }
}


void t_Trace::set_max_values(size_t  value)
{
    max_values = value;
}


void t_Trace::set_colour(int r, int g, int b)
{
    mr = r;
    mg = g;
    mb = b;
}

float t_Trace::get_min() const
{
    float tmp;
    t_Valuelist::const_iterator itor;
    tmp = (*Data.begin());
    for (itor = Data.begin(); itor != Data.end(); itor++)
    {
        if ((*itor) < tmp)
        {
            tmp = (*itor);
        }
    }
    return tmp;
}

float t_Trace::get_max() const
{

    float tmp;
    t_Valuelist::const_iterator itor;
    tmp = (*Data.begin());
    for (itor = Data.begin(); itor != Data.end(); itor++)
    {
        if ((*itor) > tmp)
        {
            tmp = (*itor);
        }
    }
    return tmp;
}

size_t t_Trace::get_size() const
{
    return Data.size();
}

t_Valuelist * t_Trace::get_Data()
{
    return &Data;
}

t_Trace::t_Trace()
{
    max_values = 200;
}
