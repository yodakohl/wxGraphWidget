// *** ADDED BY HEADER FIXUP ***
#include <wx/brush.h>
#include <wx/colour.h>
#include <wx/dcclient.h>
#include <wx/gdicmn.h>
#include <wx/panel.h>
#include <wx/pen.h>
// *** END ***
#include "statistik.h"


/**Farbwerte von der Trace holen und mit Farbe zeichnen
Skala Implementieren*/


void t_Chart::OnPaint(wxPaintEvent& event)
{

    calculate_autoscaling();

    /* ------------Painter Settings ----------------------------------------------*/
    wxPaintDC dc(this);
    wxPen pen(wxColour(0,0,250),6);
    pen.SetStyle(wxSOLID);
    wxBrush brush;
    brush.SetColour(0,100,200);
    dc.SetBrush(brush);

    /* ------------Draw Background------------------------------------------ */
    brush.SetColour(m_r,m_b,m_g);
    dc.SetBrush(brush);
    wxRect statistik_back(0, 0,chartsize_x,chartsize_y);
    dc.DrawRectangle(statistik_back);

    //Draw scaling
    brush.SetColour(0,0,0);
    dc.SetBrush(brush);

    int l_pos_x;
    int l_pos_y;

    t_Dataset::const_iterator s_itor;
    //Draw Data
    for (s_itor = Data.begin(); s_itor != Data.end(); s_itor++)
    {

        //Datesatz holen
        t_Valuelist *Values = (*s_itor)->get_Data();

        //akt_colour = (*s_itor)->get_trace_colour();
        t_Valuelist::iterator Value_itor = Values->begin();

        int current_pos = 0;
        float x = 0;
        float y = 0;
        l_pos_x = 0;
        l_pos_y = 0;

        for (Value_itor = Values->begin(); Value_itor != Values->end(); Value_itor++)
        {
            current_pos++;
            x = current_pos * scale_x;
            y = ((*Value_itor) + offset_y) * scale_y ;
            dc.DrawLine(x,chartsize_y-y,l_pos_x,l_pos_y);
            dc.DrawPoint(x,chartsize_y-y);//Draw Datadot
            l_pos_x = x;
            l_pos_y = chartsize_y-y;
        }
    }
}


t_Chart::t_Chart(wxWindow* parent, int id): wxPanel(parent,id)
{
    Connect(wxEVT_PAINT,wxPaintEventHandler(t_Chart::OnPaint));
    set_name("Unnamed Chart");
    set_size(200 , 200);
    m_r = 255;
    m_g = 255;
    m_b = 255;
}

t_Chart::~t_Chart()
{
    ///Delete All Traces
    t_Dataset::iterator itor;
    for(itor = Data.begin(); itor != Data.end(); itor++)
    {
        delete (*itor);
    }
}



void t_Chart::set_name(std::string const & value)
{
    name = value;
}

void t_Chart::set_size(size_t const & x , size_t const & y)
{
    chartsize_x = x;
    chartsize_y = y;
    SetSize(x,y);
}

void t_Chart::calculate_autoscaling()
{
    //Multitrace Autoscaling
    t_Dataset::iterator  s_itor = Data.begin();
    min = (*Data.begin())->get_min();
    max = (*Data.begin())->get_max();
    //Min und Max Werte ermitteln
    for (s_itor = Data.begin(); s_itor != Data.end(); s_itor++)
    {
        if ((*s_itor)->get_min()< min)
        {
            min = (*s_itor)->get_min();
        }
        if ((*s_itor)->get_max()> max)
        {
            max = (*s_itor)->get_max();
        }
        if ((*s_itor)->get_size()>max_x)
        {
            max_x = (*s_itor)->get_size();
        }
    }
    //  calculate scalings
    offset_y = -min;
    if ((max-min ) != 0)
    {
        scale_y = chartsize_y / (max-min);
    }
    else
    {
        scale_y = 0;
    }
    if (max_x != 0)
    {
        scale_x = chartsize_x / max_x;
    }
    else
    {
        scale_x = 0;
    }

}


t_Trace* t_Chart::add_Trace()
{
    t_Trace *p_Trace = new t_Trace;      //Datenliste dynamisch anlegen
    Data.push_back(p_Trace);             //Zum set hinzufügen
    return p_Trace;                      //Identifier zurückgegben
}

void t_Chart::repaint()
{
    Refresh();    //Manual repaint
}

void t_Chart::set_color(int r, int g , int b)
{
    m_r = r;
    m_g = g;
    m_b = b;
}
