#include <elements.hpp>
#include <custom_elements.hpp>

using namespace cycfi::elements;
using namespace blf::custom_elements;

// main window background color
auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto constexpr draw_color = rgba(255, 255, 255, 255);

auto background = box(bkd_color);
auto plot = graph(draw_color, nullptr, nullptr);

int main(int argc, char** argv)
{
    // create data to draw
    // int N = 100;
    // double *ydata = nullptr, *xdata = nullptr;
    // ydata = new double[N];
    // xdata = new double[N];
    // for(int i=0; i<N; i++)
    // {
    //     // y = x --> just draw a line
    //     ydata[i] = (double) i;
    //     xdata[i] = (double) i;
    // }


    // run app
    app _app(argc, argv, "Modern GUI", "com.cycfi.mgui");
    window _win(_app.name());
    _win.on_close = [&_app]() { _app.stop(); };

    view view_(_win);

    // All app designs happen here!
    view_.content(
        // lowest layer is at the bottom, add more ontop of it or replace background
        plot,
        background
    );

    _app.run();

    // mem clean up
    // delete[] ydata;
    // delete[] xdata;

    return 0;
}
