


//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

void DrawCircle(float cx, float cy, float r, int num_segments) ;

void DrawCircleBorder(float cx, float cy, float r, int num_segments) ;

void DrawSemiCircleBorder(float cx, float cy, float r, int num_segments) ;

void DrawEllipsoidBorder(float width,float height);

void DrawFilledEllipsoid(float width,float height);

void DrawMainCube(float width,float height);

void DrawArc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments);

void DrawSemiCircleFilled(float cx, float cy, float r, int num_segments);

void drawSeats(int number);

void drawHorse(float radiusFromTrackCenter);

void processSpecialKeys(int key, int xx, int yy);

void processNormalKeys(unsigned char key, int x, int y) ;

void processSpecialKeys(int key, int x, int y) ;

void axes();