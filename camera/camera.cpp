#include "camera/camera.h"

float Camera::getZoom(float deltaTime)
{
    if (zoom != Zoom) {
        if (dZoom < 0 && zoom > Zoom) {
            zoom += dZoom * ( deltaTime / 0.3 );
        }
        if (dZoom < 0 && zoom < Zoom) {
            dZoom = 0;
            zoom = Zoom;
        }
        if (dZoom > 0 && zoom < Zoom) {
            zoom += dZoom * ( deltaTime / 0.3 );
        }
        if (dZoom > 0 && zoom > Zoom) {
            dZoom = 0;
            zoom = Zoom;
        }
    }
    return zoom;
}

void Camera::ProcessMouseScroll(float yoffset)
{
    yoffset *= ScrollSensitivity;
    if (Zoom >= 1.0f && Zoom <= 45.0f) {
        Zoom -= yoffset;
        dZoom -= yoffset;
    }
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}
