/**-----------------------------------------------------------
Autor       : Neumair Günther
Class       : STATISTIK
Date        : 06.11.2010
LastChange  : 06.11.2010
Description : Shows Data
-------------------------------------------------------------*/

#ifndef STATISTIK_H
#define STATISTIK_H

#include <wx/wx.h>
#include <wx/event.h>
#include <wx/window.h>
#include <list>
#include <string>
#include "trace.h"

typedef std::list<t_Trace*> t_Dataset;

class t_Chart : public wxPanel
{

public:

    t_Chart(wxWindow* parent, int id);
    virtual ~t_Chart();
    /*----------------------------------   Getters && Setters  -----------------------------------------*/
    t_Trace* add_Trace();                                //add a new trace and returns identifier
    void clear_Data ();					                 //erase all data
    bool toggle_view(); 				                 //choose view type(logarithmic or linear)
    void set_name(std::string const &value);	         //set chartname
    void set_size(size_t const & x , size_t const & y);	 //set chartsize
    void OnPaint(wxPaintEvent& event);                   //Paint event
    void repaint();                                      //Force Repaint
    void set_color(int r, int g , int b);                //Set Background Color

private:

    void calculate_autoscaling();
    /*----------- Setups -----------*/
    size_t chartsize_x;
    size_t chartsize_y;
    std::string name;
    /*---------Autoscaling------------*/
    float   min;
    float   max;
    size_t  max_x;
    float   scale_x;
    float   scale_y;
    float   offset_y;
    /*---------Data -----------------*/
    t_Dataset Data;
    int m_r;
    int m_g;
    int m_b;//Farbe
};

#endif // STATISTIK_H
