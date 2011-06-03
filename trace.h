/**-----------------------------------------------------------
Autor       : Neumair Günther
Class       : TRACE
Date        : 06.11.2010
LastChange  : 06.11.2010
Description : Datacontainer for Chart
-------------------------------------------------------------*/

/// TODO MIN,MAX durch STL Algos ersetzen

#ifndef TRACE_H
#define TRACE_H

#include <wx/wx.h>
#include <list>
#include <sstream>
#include <string>

typedef std::list<float> t_Valuelist;

class t_Trace
{

public:

    t_Trace();

    void add_Data(float const &value);   ///Add a value to Trace
    void set_max_values(size_t value); 	 ///Set a valuelimit. FIFO Style , old values dissapear
    float get_max() const ;              ///Get the highest value of Trace  (Autoscaling)              TODO SPEEDUP USE STL !!!!!!!!!/
    float get_min() const ;              ///Get lowest value of Trace ( Autoscaling)                   TODO SPEEDUP USE STL !!!!!!!!!/
    size_t get_size() const;             ///Return Datacount  (Autoscaling)
    t_Valuelist * get_Data();            ///Retrieve all Data
    void set_colour(int r, int g, int b);///Set the Color of the Trace

private:

    t_Valuelist Data;
    size_t max_values;
    int mr,mg,mb;
};

#endif
