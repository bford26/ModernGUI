#if !defined(ELEMENTS_PLAYGROUND_AUG_26_2021)
#define ELEMENTS_PLAYGROUND_AUG_26_2021

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

        // elements have a draw function


        namespace p5
        {
            
            struct vertex
            {
                float* cart_coords;
                float* elli_coords;

                // vertex();
            };

            struct arc
            {
                vertex start;
                vertex end;
                float angle;
            };

            // 2D primitives 
            // arc, ellipse, circle, line, point, quad, rect, square, triangle

            // 3D primitives
            // plane, box, sphere, cylinder, cone, ellipsoid, torus, 







            class Environment
            {
                public:
                    Environment();
                    ~Environment();

                public:
                    // function that will translate into a element based struct
                    
                private:
                    camera cam;
            };

            

            struct frustum
            {
                float left;
                float right;
                float bottom;
                float top;
                float near;
                float far;
            };

            class camera
            {
            public:
                camera();
                ~camera();

            public:
                void move(float dx, float dy, float dz);        //move position by certain amount in world-space mainttaining orientation
                void moveTo(float x_, float y_, float z_);      //move to postion in world-space maintaining current cam orientation 

                void pan(float angle_);                         // rotates left and right
                void tilt(float angle_);                        // rotates up and down
                void zoom(float percentage);                    // move camera back and forth use frustum ??
                void lookAt(float x_, float y_, float z_);      // pans and tilts camera to look at a specific spot
            
            public:



            private:
                float x;
                float y;
                float z;
                float centerX;
                float centerY;
                float centerZ;
                float upX;
                float upY;
                float upZ;

            private:
                bool ortho;

                float fovy;
                float aspect;
                float perspec_near;
                float perspec_far;

                frustum frstm;
            };

            






        }



    }
}