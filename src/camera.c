#include "raylib.h"
#include "rcamera.h"


void camera_look(Camera3D* camera) {
    Vector2 mousePositionDelta = GetMouseDelta();
    
    #define CAMERA_MOVE_SPEED                               5.4f       // Units per second
    #define CAMERA_ROTATION_SPEED                           0.03f
    #define CAMERA_PAN_SPEED                                0.2f

    // Camera mouse movement sensitivity
    #define CAMERA_MOUSE_MOVE_SENSITIVITY                   0.003f

    // Camera orbital speed in CAMERA_ORBITAL mode
    #define CAMERA_ORBITAL_SPEED                            0.5f       // Radians per second
  
    // Camera speeds based on frame time
    float cameraMoveSpeed = CAMERA_MOVE_SPEED*GetFrameTime();
    float cameraRotationSpeed = CAMERA_ROTATION_SPEED*GetFrameTime();
    float cameraPanSpeed = CAMERA_PAN_SPEED*GetFrameTime();
    float cameraOrbitalSpeed = CAMERA_ORBITAL_SPEED*GetFrameTime();
    
    bool moveInWorldPlane = false;
    bool rotateAroundTarget = false;
    bool lockView = false;
    bool rotateUp = false;

    // Camera rotation
    if (IsKeyDown(KEY_DOWN)) CameraPitch(camera, -cameraRotationSpeed, lockView, rotateAroundTarget, rotateUp);
    if (IsKeyDown(KEY_UP)) CameraPitch(camera, cameraRotationSpeed, lockView, rotateAroundTarget, rotateUp);
    if (IsKeyDown(KEY_RIGHT)) CameraYaw(camera, -cameraRotationSpeed, rotateAroundTarget);
    if (IsKeyDown(KEY_LEFT)) CameraYaw(camera, cameraRotationSpeed, rotateAroundTarget);
    if (IsKeyDown(KEY_Q)) CameraRoll(camera, -cameraRotationSpeed);
    if (IsKeyDown(KEY_E)) CameraRoll(camera, cameraRotationSpeed);

    // Camera movement
    // Camera pan (for CAMERA_FREE)
    // Mouse support
    CameraYaw(camera, -mousePositionDelta.x*CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
    CameraPitch(camera, -mousePositionDelta.y*CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);

    // Keyboard support (MOVEMENT)
    /*
    if (IsKeyDown(KEY_W)) CameraMoveForward(camera, cameraMoveSpeed, moveInWorldPlane);
    if (IsKeyDown(KEY_A)) CameraMoveRight(camera, -cameraMoveSpeed, moveInWorldPlane);
    if (IsKeyDown(KEY_S)) CameraMoveForward(camera, -cameraMoveSpeed, moveInWorldPlane);
    if (IsKeyDown(KEY_D)) CameraMoveRight(camera, cameraMoveSpeed, moveInWorldPlane);
    */

    // Gamepad movement
    if (IsGamepadAvailable(0))
    {
        // Gamepad controller support
        CameraYaw(camera, -(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X)*2)*CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
        CameraPitch(camera, -(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y)*2)*CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);

        /* MOVEMENT
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) <= -0.25f) CameraMoveForward(camera, cameraMoveSpeed, moveInWorldPlane);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) <= -0.25f) CameraMoveRight(camera, -cameraMoveSpeed, moveInWorldPlane);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) >= 0.25f) CameraMoveForward(camera, -cameraMoveSpeed, moveInWorldPlane);
        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) >= 0.25f) CameraMoveRight(camera, cameraMoveSpeed, moveInWorldPlane);
        */
    }
}
