#if !defined(ELEMENTS_GRAPH_JULY_28_2021)
#define ELEMENTS_GRAPH_JULY_28_2021

#include <elements/element/element.hpp>
#include <elements/element/proxy.hpp>
#include <elements/element/text.hpp>
#include <elements/element/size.hpp>
#include <elements/support/theme.hpp>
#include <infra/support.hpp>

#include <functional>
#include <utility>

using namespace cycfi::elements;

namespace blf 
{
    namespace custom_elements
    {

        ////////////////////////////////////////////////////////////////////////////
        // Graph: A simple graph.
        ////////////////////////////////////////////////////////////////////////////
        struct graph_element : element
        {
            
            graph_element(color color_, double* x_, double* y_) : _color{color_}, _x{x_}, _y{y_} {}

            void draw(context const& ctx) override
            {
                
                auto& cnv = ctx.canvas;

                // int n = 100 - 1;
                // for(int i=0; i<n; i++)
                // {

                // } 

                // cnv.begin_path();
                cnv.arc( {50.0, 50.0}, 15, 0.0, 3.14, true);
                // cnv.close_path();
                // cnv.fill_style(_color);

                cnv.stroke_style(_color);
                cnv.stroke_preserve();
                cnv.line_width(1.0);
                cnv.stroke();


            }

            color _color;
            double* _x;
            double* _y;

        };
        
        inline auto graph(color color_, double* x_, double* y_)
        {
            return graph_element{ color_, x_, y_ };
        }

        ////////////////////////////////////////////////////////////////////////////
        // CompleteGraph: A simple graph.
        ////////////////////////////////////////////////////////////////////////////

        class Axis
        {
        public:
            
            Axis(point lim_) : lim{lim_}, scale{ "lin" }
            {

            }

            ~Axis()
            {
                if(scale!=nullptr)
                    delete scale;
                if(ticks!=nullptr)
                    delete ticks;
                if(tickLabels!=nullptr)
                    delete[] tickLabels;
            }

        private:
            
            point lim;
            
            char* scale = nullptr;
            double* ticks = nullptr;
            char** tickLabels = nullptr;
        }

        class Figure
        {

        // this will contain everything to do with a plotted set of data
        public:

            Figure()
            {

            }

            ~Figure()
            {
                if(xlabel!=nullptr)
                    delete xlabel;
                if(ylabel!=nullptr)
                    delete ylabel;
                if(title!=nullptr)
                    delete title;
            }

        public:

            void draw();

        private:

            Axis *x_axes, *y_axis;
            Axis y_axes;

            point faceSize;
            // left, top, right bottom
            rect edgeDimensions;

            // white, background of the data
            color facecolor;
            // color around face, where tick symbols go
            color edgecolor;
            
            // float linewidth;
            bool sharex, sharey;

            float dpi;
            char* xlabel = nullptr;
            char* ylabel = nullptr;
            char* title = nullptr;

        }

    }
}

#endif