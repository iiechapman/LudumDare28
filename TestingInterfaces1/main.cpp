// ============================================================================
// [Include Section]
// ============================================================================

//Working on windows version

#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <random>
#include "Renderer.h"
#include "Actor.h"
#include "RenderableShape.h"
#include "RenderableSprite.h"
#include "MoveAction.h"
#include "timer.h"
#include "GravityAction.h"
#include "Definitions.h"

// ============================================================================
// [SdlApplication]
// ============================================================================
#pragma mark - Definitions

#define APPTITLE "LD 28 - Luminess"
// SdlApplication is nothing more than thin wrapper to SDL library. You need
// just to instantiate it and call run() to enter the SDL event loop.


//-------------------------------------------
#pragma mark Global Values


typedef vector<Actor*>* ActorList;
typedef vector<MoveAction*>* ActionList;


enum GameStates
{
    VINDINCE,DET,LUDUM,TITLE,CLEAN,LOADLEVEL,LOADBANNER,BANNER,LEVEL,WON,FINAL
};

string currentBanner;

GameStates GAME_STATE = LOADBANNER;
unsigned long CURRENT_LEVEL = 0;
long LAST_LEVEL = 10;

bool playerAlive = true;
bool playerWinning = false;

unsigned int slowDown = 0;

float frictionSpeed  = .900;
float moveSpeed      = .0008;

float bounceRecoil   = .3;
bool fullScreenMode  = false;
bool playMusic       = true;

bool playerSpawned = false;

dimensions_t playerBounds;

int bannerTime = 700;
int bannerTimer = bannerTime;

Timer*      gameTimer;

float cameraX = 0,cameraY = 0;
float startCameraX = 0, startCameraY = 0;

int bounceTime = 100;
int bounceTimer = bounceTime;


int transitionTime = 3000;
int transitionTimer = transitionTime;

int recoilTime = 50;
int recoilTimer = recoilTime;

bool pressedSpace;

int lastParticleAvailable = 0;
int totalParticlesPerCast = 1200;
const int PARTICLES_MAX = 30000;

int numberOfSmokeParticles = 1;
int numberOfGunShotParticles = 10;
int numberOfExplosionParticles = 1000;
int numberOfWarpParticles= 3000;

int shotTime = 150;
int shotTimer = shotTime;

bool onColor = false;

int portalAngle =0;

int lastPelletAvailable = 0;
const int PELLETS_MAX = 100;

dimensions_t spawnPoint;
dimensions_t stopAction;

float MAP_WIDTH,MAP_HEIGHT;

int playerWidth = 120;
int playerHeight = 100;

int SCROLLDEADZONEX = 0;
int SCROLLDEADZONEY = 0;

int SCROLLXRIGHT = SCREEN_WIDTH/2 + SCROLLDEADZONEX;
int SCROLLXLEFT = SCREEN_WIDTH/2 - SCROLLDEADZONEX;

int SCROLLYBOTTOM = SCREEN_HEIGHT/2 +SCROLLDEADZONEY;
int SCROLLYTOP = SCREEN_HEIGHT/2  -SCROLLDEADZONEY;


double circleAngle;

float aimX, aimY;
float aimTurnSpeed = 1;
float mouseX, mouseY;
float lastMouseX , lastMouseY;

//Global Color Keys
//Invisibles
SDL_Color pureWhite,offWhite;

//Solid
SDL_Color solidColor;

//passables
SDL_Color bluePass;
SDL_Color yellowPass,greenPass,purplePass,cyanPass;

//kill wall
SDL_Color redKill;

//Spawnables
SDL_Color startColor, endColor;
SDL_Color enemyColor;
SDL_Color yellowKeyColor,greenKeyColor,purpleKeyColor,cyanKeyColor;
SDL_Color yellowOrbColor,greenOrbColor,purpleOrbColor,cyanOrbColor;

//Color Powers
bool    neutralActive   = true;
bool    blueActive      = false;
bool    yellowActive    = false;
bool    purpleActive    = false;
bool    cyanActive      = false;

bool    yellowKey    =false;
bool    cyanKey      =false;
bool    purpleKey    =false;

bool    allKey      =false;

enum powers {noPower,bluePower,yellowPower,purplePower,cyanPower,allPower};

powers tempPower;
powers currentPower = noPower;
powers lastPower = bluePower;

enum    particle_type
{
    PARTICLE_TYPE_SOLID,
    PARTICLE_TYPE_KILL,
    PARTICLE_TYPE_RAY,
    PARTICLE_TYPE_CORRUPT,
    PARTICLE_TYPE_PASSABLE,
    PARTICLE_TYPE_PERMANENT,
    PARTICLE_TYPE_INVISIBLE,
    PARTICLE_TYPE_SMOKE,
    PARTICLE_TYPE_GUNSHOT,
    PARTICLE_TYPE_SPARK,
    PARTICLE_TYPE_EXPLOSION,
    PARTICLE_TYPE_WARP
};

int particleTime = 100;
int particleFadeTimeFast = 10;
int particleFadeTimeMedium = 5;
int particleFadeTimeSlow = 1;


float particleTimerFast = particleTime;
float particleTimerSlow = particleTime;
float particleTimerMedium = particleTime;


vector<MoveAction*> pelletActionQueue;
vector<MoveAction*> particlesActionQueue;
vector<MoveAction*> playerActionQueue;



vector<Actor*> pellets;
vector<Actor*> actors;
vector<Actor*> scrollActors;
vector<Actor*> particles;



SDL_Window *win;

//---------------------------------------------
#pragma mark - Test Objects
Renderer*           renderer;
Actor*              particle;
RenderableShape*    particleShape;

MoveAction*         moveRight;
MoveAction*         moveUp;
MoveAction*         moveLeft;
MoveAction*         moveDown;
MoveAction*         currentAction;
GravityAction*      gravityAction;


//MoveAction*         playerMoveRight;
//MoveAction*         playerMoveLeft;
//MoveAction*         playerMoveDown;
MoveAction*         playerMoveUp;


Mix_Music*          s_Song1;

Mix_Chunk*          s_Bounce;
Mix_Chunk*          s_Death;
Mix_Chunk*          s_Shoot;
Mix_Chunk*          s_Blood;
Mix_Chunk*          s_Orb;
Mix_Chunk*          s_End;



TTF_Font*           f_TestFont;

SDL_Surface*        textSurface;
SDL_Texture*        textTexture;

SDL_Surface*        imageSurface;
SDL_Texture*        imageTexture;
SDL_Rect            imageRect;

SDL_Surface*        mapSurface;

SDL_Color           mapColor;

Uint8*              checkPixel;

SDL_Surface*        playerSpriteSurface;
RenderableSprite*   playerSprite;
Actor*              playerActor;

SDL_Surface*        armSpriteSurface;
RenderableSprite*   armSprite;
Actor*              armActor;


SDL_Surface*        pelletSurface;
RenderableSprite*   pelletSprite;
Actor*              pelletActor;


SDL_Surface*        cursorSurface;
RenderableSprite*   cursorSprite;
Actor*              cursorActor;

SDL_Surface*        portalSurface;
RenderableSprite*   portalSprite;
Actor*              portalActor;


SDL_Surface*        blueOrbSurface;
RenderableSprite*   blueOrbSprite;
Actor*              blueOrbActor;

SDL_Surface*        cyanOrbSurface;
RenderableSprite*   cyanOrbSprite;
Actor*              cyanOrbActor;

SDL_Surface*        yellowOrbSurface;
RenderableSprite*   yellowOrbSprite;
Actor*              yellowOrbActor;

SDL_Surface*        purpleOrbSurface;
RenderableSprite*   purpleOrbSprite;
Actor*              purpleOrbActor;

SDL_Surface*        bannerSurface;
RenderableSprite*   bannerSprite;
Actor*              bannerActor;


SDL_Surface*        yellowKeySurface;
RenderableSprite*   yellowKeySprite;
Actor*              yellowKeyActor;

SDL_Surface*        cyanKeySurface;
RenderableSprite*   cyanKeySprite;
Actor*              cyanKeyActor;

SDL_Surface*        purpleKeySurface;
RenderableSprite*   purpleKeySprite;
Actor*              purpleKeyActor;


RenderableSprite*   orbSprite;


MoveAction*         pelletMovement;
GravityAction*      pelletGravity;

dimensions_t        pelletTrajectory;
dimensions_t        ejectDirection;

bool                pelletAlive;

button_t            buttonUp,buttonNext,buttonDown,buttonRight,buttonLeft,buttonShoot,buttonJump,buttonPowerSwitch;



//--------------------------------------------------
#pragma mark - Test Function Declaration
void ChangeFullScreen(bool fullscreen);
void PrintDynamicMemory();


//Game State code
void LoadLevel(SDL_Renderer* sdlRenderer);
void LoadLevelBanner();
void CleanLevel();
void LoadFinalBanner();
void CheckForStartGame();
void LoadBanner(SDL_Renderer* sdlRenderer);
void CreateBanner(SDL_Renderer* sdlRenderer);


void CreateParticles();
void PlaceParticles(float x, float y);
void ReverseParticlesMotion();
void ActionsQueueTest();
void CheckForBounds();

void PlacePortal();
void CheckShoot();
void HideSprites();

bool DidCollide(RenderableSprite* spriteA, RenderableSprite* spriteB);

void CreatePlayerActions();

void PlaceCannonOnPlayer();

void ShootPelletFromPlayer();

void SetMapColorKey();
bool SameColor(SDL_Color color1 , SDL_Color color2);

void CheckScroll();
void PlaceShipInCenter();

void RotateSprite();
void PlaceKeys();
void CheckActivePower();
void PlaceOrbsAroundShip();

void CheckShipCollision();

void InitSound();
void OpenAudio();
void LoadSounds();
void TestMusic();
void PlaySound(Mix_Chunk *sound);

void PlayerWin();
void RotatePortal();

void UpdateParticles(Uint32 delta);
void PlaceParticleAt(Actor* particle, float x, float y);

void InitTTF();
void LoadFont();
void RenderText(SDL_Renderer *renderer);

void LoadPlayerSprite(SDL_Renderer *renderer);

void CreateSpriteAtPos(float x, float y);
Actor* CreateActorAtPos(RenderableSprite* sprite,float x, float y);
void LoadSprite(SDL_Renderer* sdlRenderer,char* file);

RenderableSprite* LoadSprite(RenderableSprite* sprite,string file,SDL_Renderer* sdlRenderer, int w, int h);

void PlaceSpriteAt(float x, float y);
void PlaceActorAt(Actor* actor, float x, float y);

void RotateSpriteTowardsPos(float x, float y);

void MoveAim();

void LoadPelletSprite(SDL_Renderer *sdlRenderer);
void CreatePelletAtPos(float x , float y);
void CreatePellets(SDL_Renderer *renderer);

vector<Actor*>::iterator DeleteParticle(Actor* deadParticle);

void CheckPelletCollision();
void DeletePellet(Actor* pellet);

void ThrowRaysFromPellet();
void CastRaysFromPellet(Actor* pellet);

void SetParticleType(Actor* particle, particle_type type);

void CalculateEjectDirection();

void CheckControls(Uint32 delta);

void CreateParticlesAt(int num ,float x, float y);

void SetCamera();
void SetCameraTo(float x ,float y);

void PrintCameraPos();

void LoadSpawnPoint();

void PlayerKill();

void CreatePortal(SDL_Renderer* sdlRenderer);


dimensions_t CalculateVectorDifference(dimensions_t dim1 , dimensions_t dim2);


Uint8* GetPixel( SDL_Surface *surface, int x, int y );
SDL_Color GetPixelColor(Uint32 pixel, SDL_Surface* surface);


SDL_Texture* ConvertSurfaceToTexture(SDL_Renderer* renderer , SDL_Surface* surface);


void InitImage();
void LoadImageTest();



//-------------------------------------------------
#pragma mark - SDL Application Struct
//Start SDL app struct
struct SdlApplication
{
	SdlApplication();
	~SdlApplication();
	
	// Application state (just convenience instead of 0, 1, ...).
	enum APP_STATE
	{
		APP_OK = 0,
		APP_FAILED = 1
	};
	
	// Initialize application, called by run(), don't call manually.
	int init(int width, int height);
	
	// Destroy application, called by destructor, don't call manually.
	void destroy();
	
	// Run application, called by your code.
	int run(int width, int height);
    
	// Called to process SDL event.
	void onEvent(SDL_Event* ev);
	
	// Called to render content into buffer.
	void Render();
	
	// Whether the application is in event loop.
	bool _running;
	SDL_Renderer *sdlRenderer;
};

SdlApplication::SdlApplication() :
_running(false)
{
}

SdlApplication::~SdlApplication()
{
	destroy();
}

int SdlApplication::init(int width, int height)
{
	// Initialize the SDL library.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return APP_FAILED;
	}
	
	win = SDL_CreateWindow(APPTITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	sdlRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	
    
    ChangeFullScreen(fullScreenMode);
    
    //CREATE GAME ENGINE OBJECTS
    renderer    = new Renderer();
    gameTimer   = new Timer();
    
    
    //Load sounds and music
    InitSound();
    OpenAudio();
    LoadSounds();

    stopAction.x =0;
    stopAction.y =0;
    
    //Build Color Key
    SetMapColorKey();
    //InitTTF();
    //LoadFont();
    //RenderText(sdlRenderer);


    CreateBanner(sdlRenderer);
    
	// Success.
	return APP_OK;
}

void SdlApplication::destroy()
{
	if (win)
	{
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(sdlRenderer);
        
        delete renderer;
        delete particle;
        delete particleShape;
        delete moveRight;
        delete moveLeft;
        delete moveDown;
        delete currentAction;
        delete gravityAction;

        delete playerMoveUp;
//        delete playerMoveRight;
//        delete playerMoveLeft;
//
//        delete playerMoveDown;
        

        delete s_Blood;

        
        SDL_FreeSurface(textSurface);
        
        delete textSurface;
        
        SDL_FreeSurface(imageSurface);
    
    
        SDL_FreeSurface(mapSurface);
        
        for (actionIter i = pelletActionQueue.begin();
             i != pelletActionQueue.end();
             )
        {
            i = pelletActionQueue.erase(i);
        }
        
        
        for (actorIter i = actors.begin();
             i != actors.end();
             )
        {
            i = actors.erase(i);
        }
        IMG_Quit();
		SDL_Quit();
	}
}

int SdlApplication::run(int width, int height)
{
	// Initialize application
	int state = init(width, height);
	if (state != APP_OK) return state;
	
    InitImage();

    
    CreatePortal(sdlRenderer);
    
    //Create all Particles
    CreateParticlesAt(PARTICLES_MAX + totalParticlesPerCast,-3000,90000);
    CreatePellets(sdlRenderer);
    
    for (actorIter i = pellets.begin();
         i !=pellets.end();
         i++)
    {
        DeletePellet((*i));
    }
    
    for (actorIter i = particles.begin();
         i !=particles.end();
         i++)
    {
        PlaceParticleAt((*i), -2000, 2000);
    }
    
    
    //Load sprite
    LoadPlayerSprite(sdlRenderer);
    
    
    //Load files
    string file  = "bluebubble.png";
    orbSprite = LoadSprite(orbSprite,file, sdlRenderer, 150, 150);
    blueOrbActor = CreateActorAtPos(orbSprite, 0, 0);
    
    file  = "yellowbubble.png";
    orbSprite = LoadSprite(orbSprite,file, sdlRenderer, 150, 150);
    yellowOrbActor = CreateActorAtPos(orbSprite, 0, 0);
    
    file  = "cyanbubble.png";
    orbSprite = LoadSprite(orbSprite,file, sdlRenderer, 150, 150);
    cyanOrbActor = CreateActorAtPos(orbSprite, 0, 0);
    
    file  = "pinkbubble.png";
    orbSprite = LoadSprite(orbSprite,file, sdlRenderer, 150, 150);
    purpleOrbActor = CreateActorAtPos(orbSprite, 0, 0);
    



    //Make Yellow key
    SDL_Rect* position = new SDL_Rect;
    
    yellowKeySurface=IMG_Load("yellowbubble.png");
    if(!yellowKeySurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }
    yellowKeySprite = new RenderableSprite();
    Color color;
    color.red = 255;
    color.green = 0;
    color.blue = 0;
    position->x = 1;
    position->y = 1;
    position->w = 100;
    position->h = 100;
    yellowKeySprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, yellowKeySurface));
    yellowKeySprite->SetScaleX(1);
    yellowKeySprite->SetScaleY(1);
    yellowKeySprite->SetCenter(0,0);
    yellowKeySprite->SetColor(color);
    yellowKeySprite->SetSrc(NULL);
    yellowKeySprite->SetDst(position);
    yellowKeySprite->SetFlip(SDL_FLIP_NONE);
    yellowKeyActor = new Actor();
    yellowKeyActor->SetMotion(false);
    yellowKeyActor->SetPosX(100);
    yellowKeyActor->SetPosY(100);
    yellowKeyActor->SetActorView(yellowKeySprite);
    scrollActors.push_back(yellowKeyActor);
    renderer->AddRenderable(yellowKeySprite);
    yellowKeyActor->GetActorView()->SetCameraFollow(true);
    
    cyanKeySurface=IMG_Load("cyanbubble.png");
    if(!cyanKeySurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }
    cyanKeySprite = new RenderableSprite();
    color.red = 255;
    color.green = 0;
    color.blue = 0;
    position->x = 1;
    position->y = 1;
    position->w = 100;
    position->h = 100;
    cyanKeySprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, cyanKeySurface));
    cyanKeySprite->SetScaleX(1);
    cyanKeySprite->SetScaleY(1);
    cyanKeySprite->SetCenter(0,0);
    cyanKeySprite->SetColor(color);
    cyanKeySprite->SetSrc(NULL);
    cyanKeySprite->SetDst(position);
    cyanKeySprite->SetFlip(SDL_FLIP_NONE);
    cyanKeyActor = new Actor();
    cyanKeyActor->SetMotion(false);
    cyanKeyActor->SetPosX(100);
    cyanKeyActor->SetPosY(100);
    cyanKeyActor->SetActorView(cyanKeySprite);
    scrollActors.push_back(cyanKeyActor);
    renderer->AddRenderable(cyanKeySprite);
    cyanKeyActor->GetActorView()->SetCameraFollow(true);
    
    purpleKeySurface=IMG_Load("pinkbubble.png");
    if(!purpleKeySurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }
    purpleKeySprite = new RenderableSprite();
    color.red = 255;
    color.green = 0;
    color.blue = 0;
    position->x = 1;
    position->y = 1;
    position->w = 100;
    position->h = 100;
    purpleKeySprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, purpleKeySurface));
    purpleKeySprite->SetScaleX(1);
    purpleKeySprite->SetScaleY(1);
    purpleKeySprite->SetCenter(0,0);
    purpleKeySprite->SetColor(color);
    purpleKeySprite->SetSrc(NULL);
    purpleKeySprite->SetDst(position);
    purpleKeySprite->SetFlip(SDL_FLIP_NONE);
    purpleKeyActor = new Actor();
    purpleKeyActor->SetMotion(false);
    purpleKeyActor->SetPosX(100);
    purpleKeyActor->SetPosY(100);
    purpleKeyActor->SetActorView(purpleKeySprite);
    scrollActors.push_back(purpleKeyActor);
    renderer->AddRenderable(purpleKeySprite);
    purpleKeyActor->GetActorView()->SetCameraFollow(true);

    
    playerActor = CreateActorAtPos(playerSprite,0, 0);
    cursorActor = CreateActorAtPos(cursorSprite, 0, 0);
    armActor    = CreateActorAtPos(armSprite, 0, 0);
    
    CreatePlayerActions();
    
    playerActor->GetActorView()->SetCameraFollow(false);
    cursorActor->GetActorView()->SetCameraFollow(false);
    

    
    
	// Enter to the SDL event loop.
	SDL_Event ev;
	_running = true;
	
    if (playMusic)
    {
        //play Starting music
        TestMusic();
    }
    
	while (_running)
	{
        gameTimer->Update();
        while (SDL_PollEvent(&ev))
        {
            onEvent(&ev);
        }
        
        SDL_ShowCursor(0);
        SDL_bool mouseTrapped = SDL_TRUE;
        SDL_SetRelativeMouseMode(mouseTrapped);
        
        switch (GAME_STATE)
        {
            case LEVEL:
                if (playerAlive && !playerWinning)
                {
                    PlaceActorAt(cursorActor,mouseX - 20, mouseY- 20);
                    CheckControls(gameTimer->GetDelta());
                    CheckShipCollision();
                    CheckShoot();
                    RotateSpriteTowardsPos(mouseX,mouseY);
                    CheckScroll();
                } else {
                    playerMoveUp->SetDisplacement(stopAction);
                    playerActor->SetPosX(-2000);
                    playerActor->SetPosY(2000);
                    transitionTimer-= gameTimer->GetDelta();
                    
                    for (actorIter i = scrollActors.begin();
                         i != scrollActors.end();
                         i ++)
                    {
                        (*i)->SetPosY(2000);
                        (*i)->SetPosX(-2000);
                    }
                    
                    for (actorIter i = pellets.begin();
                         i != pellets.end();
                         i ++)
                    {
                        (*i)->SetPosY(2000);
                        (*i)->SetPosX(MAP_WIDTH + 1000);
                    }
                    
                    cursorActor->SetPosX(-2000);
                    cursorActor->SetPosY(2000);
                    
                    if (transitionTimer<=0)
                    {
                        transitionTimer = 0;
                        
                        if (!playerAlive)
                        {
                            GAME_STATE = LOADBANNER;
                        }
                        
                        if (playerWinning)
                        {
                            GAME_STATE = LOADBANNER;
                        }
                    }
                }
                
                playerMoveUp->Start();
                MoveAim();
                CheckActivePower();
                ActionsQueueTest();
                SetCamera();
                CalculateEjectDirection();
                CheckPelletCollision();
                CheckForBounds();
                PlaceCannonOnPlayer();
                PlaceOrbsAroundShip();
                UpdateParticles(gameTimer->GetDelta());
                break;
                
            case CLEAN:
                playerSpawned = false;
                HideSprites();
                CleanLevel();
                break;
                
                
            case LOADLEVEL:
                HideSprites();
                playerMoveUp->Stop();
                playerSpawned = false;
                LoadLevel(sdlRenderer);
                break;
                
                
            case LOADBANNER:
                HideSprites();
                bannerTimer = bannerTime;
                playerMoveUp->Stop();
                LoadBanner(sdlRenderer);
                bannerActor->SetPosY(0);
                bannerActor->SetPosX(0);
                
                GAME_STATE = BANNER;
                break;
                
                
            case BANNER:
                HideSprites();
                bannerTimer-= gameTimer->GetDelta();
                if (bannerTimer <=0)
                {
                    bannerTimer=0;
                }
                bannerActor->SetPosX(0);
                bannerActor->SetPosY(0);
                //wait for player to press button to move forward
                if (bannerTimer <=0 &&buttonNext.pressed && !buttonNext.held)
                {
                    printf("banner mode exit\n");
                    PlaySound(s_Orb);
                    
                    playerAlive = true;
                    playerWinning = false;
                    
                    GAME_STATE = CLEAN;
                }
                

                break;
                
            case VINDINCE:
                HideSprites();
                break;
                
                
            default:
                break;
        }
        
        Render();
        SDL_Delay(slowDown);
        
        if (_running == false)
        {
            break;
        }
    }
    return APP_OK;
}



void SdlApplication::onEvent(SDL_Event* ev)
{
	switch (ev->type)
	{
		case SDL_QUIT:
            _running = false;
            break;
            
        case SDL_MOUSEBUTTONDOWN:
            switch (ev->button.button)
            {
                case SDL_BUTTON_LEFT:
                    
                    if (buttonNext.pressed){
                        buttonNext.held = true;
                    }
                    buttonNext.pressed= true;
                
                    
                    break;
                
                case SDL_BUTTON_RIGHT:
                    buttonUp.pressed = true;
                    break;
                    
                default:
                    break;
            }
            break;

            
        case SDL_MOUSEBUTTONUP:
            switch (ev->button.button)
        {
            case SDL_BUTTON_RIGHT:
                buttonUp.pressed = false;
                break;
                
            case SDL_BUTTON_LEFT:
                shotTimer = 0;
                buttonNext.pressed = false;
                buttonNext.held = false;
                
            default:
                break;
        }
            
    
        case SDL_MOUSEMOTION:
            mouseX = ev->motion.x;
            mouseY = ev->motion.y;
            
            if (buttonUp.pressed || buttonUp.held){
                lastMouseX = ev->button.x;
                lastMouseY = ev->button.y;
            }
            
            break;
            
            
            
        case SDL_KEYUP:
            switch (ev->key.keysym.sym)
        {
            case SDLK_SPACE:
                buttonPowerSwitch.held = false;
                buttonPowerSwitch.pressed = false;
                break;
                
            default:
                break;
        }
            break;
            
        case SDL_KEYDOWN:
            switch (ev->key.keysym.sym)
        {
                case SDLK_ESCAPE:
                    _running = false;
                    break;
                
            case SDLK_f:
                fullScreenMode = !fullScreenMode;
                ChangeFullScreen(fullScreenMode);
                SDL_ShowCursor(true);
                buttonUp.pressed = false;
                buttonUp.held = false;
                buttonNext.pressed = false;
                buttonNext.held = false;
                playerMoveUp->SetDisplacement(stopAction);
                break;
                
            case SDLK_r:
                if (GAME_STATE == LEVEL)
                {
                    LoadSpawnPoint();
                }
                break;
                
                case SDLK_SPACE:
                //Switch powers
                if (GAME_STATE == LEVEL && !onColor)
                {
                if (buttonPowerSwitch.pressed)
                {
                    buttonPowerSwitch.held = true;
                    buttonPowerSwitch.pressed = false;
                } else {
                    buttonPowerSwitch.pressed = true;
                    PlaySound(s_Orb);
                    currentPower++;
                }
                buttonPowerSwitch.pressed = true;
                }
                break;
                
//            case SDLK_1:
//                currentPower = bluePower;
//                break;
//                
//            case SDLK_2:
//                currentPower = yellowPower;
//                break;
//
//            case SDLK_3:
//                currentPower = noPower;
//                break;
//
//            case SDLK_4:
//                currentPower = cyanPower;
//                break;
//                
//            case SDLK_5:
//                currentPower = purplePower;
//                break;
//                
//            case SDLK_0:
//                currentPower = allPower;
//                break;
                
                
                default:
                    break;
            }
            break;
	}
}

void SdlApplication::Render()
{
    renderer->RenderToFrame(sdlRenderer);
}


// ============================================================================
// [Entry-Point]
// ============================================================================
#pragma mark - Entry Point
int main(int argc, char* argv[])
{
	SdlApplication app;
	return app.run(SCREEN_WIDTH, SCREEN_HEIGHT);
}



//-------------------------------------------------------
#pragma mark - Test Function Definition

void CreateParticles()
{
    srand(static_cast <unsigned int>(time(0)));
    
    Color newColor;
    
    dimensions_t tempDisplacement;
    
    newColor.red = 50;
    newColor.blue = 50;
    newColor.green = 50;
    newColor.alpha = 0;
    
    
    //Create particle objects
    for (int i = 0 ; i < 2000 ; i++)
    {
        //Reset temporary particle object

        particle = NULL;
        particle = new Actor();
        
        particle->SetMotion(true);
        

        particleShape    = 0;
        particleShape    = new RenderableShape();
        
        float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float finalRandom = random + (rand() % 20);
        
        particle->SetWidth(finalRandom/2);
        
        // finalRandom = random + (rand() % 10);
        particle->SetHeight(finalRandom/2);
        
        
        //int randomColor = 0 + rand() % 240 + (1 * 10);
        //newColor.red = randomColor/3;
        //newColor.green = randomColor/1;
       // newColor.blue = randomColor/1;
        
        
        random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        finalRandom = (rand() % 1) + random + (rand() % 1 );
        
        finalRandom = 0;
        
        particle->SetPosX(-2000);
        particle->SetPosY(2000);
        
        particle->SetColor(newColor);
        
        //Connect actor to view object
        particle->SetActorView(particleShape);
        //Add view object to renderer
        renderer->AddRenderable(particle->GetActorView());
        
        particles.push_back(particle);
    }
    
    
    //Testing Movement Actions
    
    int randomAction;
    
    for (actorIter currentActor = particles.begin();
         currentActor != particles.end();
         currentActor++)
    {
        
        randomAction = 4;
        if (randomAction >4)
        {
            randomAction = 0;
        }
        randomAction = 4;
        
        float xSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
        //printf("X speed: %f \n", xSpeed) ;
        //float finalXSpeed = xSpeed + (rand() % 1);
        float finalXSpeed =20 + xSpeed *4;
        
        float ySpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
        //float finalYSpeed = ySpeed + (rand() % 1);
        float finalYSpeed = 20 +  ySpeed *4;
        
        tempDisplacement.y = 0;
        
        switch (randomAction)
        {
            case 0:
                tempDisplacement.y = 0;
                tempDisplacement.x = -finalXSpeed;
                moveLeft = new MoveAction(tempDisplacement);
                moveLeft->AttachTo((*currentActor));
                particlesActionQueue.push_back(moveLeft);
                (*currentActor)->AddAction(moveLeft);
                break;
                
                
            case 1:
                tempDisplacement.y = 0;
                tempDisplacement.x = finalXSpeed;
                moveRight = new MoveAction(tempDisplacement);
                moveRight->AttachTo((*currentActor));
                particlesActionQueue.push_back(moveRight);
                (*currentActor)->AddAction(moveRight);
                break;
                
            case 2:
                tempDisplacement.y = -finalXSpeed;
                tempDisplacement.x = 0;
                moveUp = new MoveAction(tempDisplacement);
                moveUp->AttachTo((*currentActor));
                particlesActionQueue.push_back(moveUp);
                (*currentActor)->AddAction(moveUp);
                break;
                
            case 3:
                tempDisplacement.y = finalXSpeed;
                tempDisplacement.x = 0;
                moveDown= new MoveAction(tempDisplacement);
                moveDown->AttachTo((*currentActor));
                particlesActionQueue.push_back(moveDown);
                (*currentActor)->AddAction(moveDown);
                break;
                
            case 4:
                bool flipVert,flipHor;
                
                flipVert = rand() % 3;
                flipHor = rand() % 3;
                
                
                if (flipVert)
                {
                    tempDisplacement.y = -finalYSpeed;
                } else
                {
                    tempDisplacement.y = finalYSpeed;
                }
                
                if (flipHor)
                {
                    tempDisplacement.x = -finalXSpeed;
                } else
                {
                    tempDisplacement.x = finalXSpeed;
                }
                moveRight->Stop();
                moveRight = new MoveAction(tempDisplacement);
                moveRight->AttachTo((*currentActor));
                particlesActionQueue.push_back(moveRight);
                (*currentActor)->AddAction(moveRight);
                break;
                
                
            default:
                break;
        } // End switch
    } // end particle make
    
    //Make Gravity actions
    for (actorIter curr = particles.begin() ;
         curr != particles.end();
         curr++)
    {
        float randomGrav = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        
        tempDisplacement.y = 1- randomGrav * 10;
        tempDisplacement.x = 0;
        gravityAction = 0;
        gravityAction = new GravityAction(tempDisplacement);
        
        gravityAction->AttachTo((*curr));
        particlesActionQueue.push_back(gravityAction);
        (*curr)->AddAction(gravityAction);
    } //end gravit action creation
}


void EjectParticles(float x , float y,int numberOfParticles)
{
    for (actionIter currentAction = particlesActionQueue.begin() + lastParticleAvailable;
         currentAction!= particlesActionQueue.begin() + lastParticleAvailable + numberOfParticles;
         currentAction++)
    {
        if (dynamic_cast<GravityAction*>(*currentAction))
        {
            GravityAction* gravAct = (GravityAction*)(*currentAction);
            gravAct->Reset();
        }
        
        (*currentAction)->Start();
    }
    
    
    for (actorIter curr = particles.begin() + lastParticleAvailable;
         curr != particles.begin() + lastParticleAvailable + numberOfParticles;
         curr++)
    {
        int randX = 1 +rand() % 1;
        int randY = 1 + rand() % 1;
        
        randX = 0;
        randY = 0;
        
        (*curr)->SetPosX(x + randX);
        (*curr)->SetPosY(y + randY);
        (*curr)->SetMotion(true);
        
        int randomColor = 1 + rand() % 30 + (1 * 10);
        
        float xSpeed,ySpeed;
        float finalXSpeed,finalYSpeed;
        bool flipVert,flipHor;
        dimensions_t tempDisplacement;
        Color newColor;
        
        
        switch ((*curr)->GetID()) {
            case PARTICLE_TYPE_RAY:
                newColor.red = randomColor + 30;
                newColor.green = randomColor + 44;
                newColor.blue = randomColor + 50;
                
                xSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
                //printf("X speed: %f \n", xSpeed) ;
                //float finalXSpeed = xSpeed + (rand() % 1);
                finalXSpeed =0 + xSpeed *2;
                
                ySpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
                //float finalYSpeed = ySpeed + (rand() % 1);
                finalYSpeed = 0 +  ySpeed *2;
                
                flipVert = rand() % 3;
                flipHor = rand() % 3;
                
                
                if (flipVert)
                {
                    tempDisplacement.y = -finalYSpeed;
                } else
                {
                    tempDisplacement.y = finalYSpeed;
                }
                
                if (flipHor)
                {
                    tempDisplacement.x = -finalXSpeed;
                } else
                {
                    tempDisplacement.x = finalXSpeed;
                }
                (*curr)->GetLastAction()->SetDisplacement(tempDisplacement);
                
                break;
                
            case PARTICLE_TYPE_SMOKE:
                newColor.red = 100;
                newColor.green = 70;
                newColor.blue = 70;
                break;
                
            case PARTICLE_TYPE_GUNSHOT:
                newColor.red = 255;
                newColor.green = 255;
                newColor.blue = 255;
                break;
                
            case PARTICLE_TYPE_WARP:
                newColor.red = 100;
                newColor.green = 150;
                newColor.blue = 255;
                
                xSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
                //printf("X speed: %f \n", xSpeed) ;
                //float finalXSpeed = xSpeed + (rand() % 1);
                finalXSpeed =0 + xSpeed *2;
                
                ySpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
                //float finalYSpeed = ySpeed + (rand() % 1);
                finalYSpeed = 0 +  ySpeed *2;
                
                flipVert = rand() % 3;
                flipHor = rand() % 3;
                
                
                if (flipVert)
                {
                    tempDisplacement.y = -finalYSpeed;
                } else
                {
                    tempDisplacement.y = finalYSpeed;
                }
                
                if (flipHor)
                {
                    tempDisplacement.x = -finalXSpeed;
                } else
                {
                    tempDisplacement.x = finalXSpeed;
                }
                (*curr)->GetLastAction()->SetDisplacement(tempDisplacement);
                break;
                
            case PARTICLE_TYPE_EXPLOSION:
                newColor.red = 200;
                newColor.green = 100;
                newColor.blue = 100;
                
                xSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
                //printf("X speed: %f \n", xSpeed) ;
                //float finalXSpeed = xSpeed + (rand() % 1);
                finalXSpeed =0 + xSpeed *2;
                
                ySpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
                //float finalYSpeed = ySpeed + (rand() % 1);
                finalYSpeed = 0 +  ySpeed *2;
                
                flipVert = rand() % 3;
                flipHor = rand() % 3;
                
                
                if (flipVert)
                {
                    tempDisplacement.y = -finalYSpeed;
                } else
                {
                    tempDisplacement.y = finalYSpeed;
                }
                
                if (flipHor)
                {
                    tempDisplacement.x = -finalXSpeed;
                } else
                {
                    tempDisplacement.x = finalXSpeed;
                }
                (*curr)->GetLastAction()->SetDisplacement(tempDisplacement);
                break;
                
            default:
                break;
        }
        
        //CONTROL COLOR HERE
        (*curr)->SetColor(newColor);
    }
    
    
    lastParticleAvailable += numberOfParticles;
    
    //printf("last particle %i \n" , lastParticleAvailable);
    
    if (lastParticleAvailable >= PARTICLES_MAX)
    {
        lastParticleAvailable = 0;
    }
}


void PlaceParticles(float x, float y)
{
    for (actionIter currentAction = particlesActionQueue.begin();
         currentAction!= particlesActionQueue.end();
         currentAction++)
    {
        if (dynamic_cast<GravityAction*>(*currentAction))
        {
            GravityAction* gravAct = (GravityAction*)(*currentAction);
            gravAct->Reset();
        }
    }
    
    for (actionIter currentAction = particlesActionQueue.begin();
         currentAction != particlesActionQueue.end() ;
         currentAction++)
    {
        (*currentAction)->Start();
    }
    
    
    for (actorIter curr = particles.begin();
         curr != particles.end();
         curr++)
    {
        int randX = 1 +rand() % 1;
        int randY = 1 + rand() % 1;
        
        randX = 0;
        randY = 0;
        
        (*curr)->SetPosX(x + randX);
        (*curr)->SetPosY(y + randY);
        (*curr)->SetMotion(true);
        
        Color newColor;
        
        int randomColor = 1 + rand() % 30 + (1 * 10);
        newColor.red = randomColor + 30;
        newColor.green = randomColor + 44;
        newColor.blue = randomColor + 50;
        
        (*curr)->SetColor(newColor);
    }
    //PlaySound(s_Blood);
    
}


void ReverseParticlesMotion()
{
    for (actionIter currentAction = particlesActionQueue.begin();
         currentAction!= particlesActionQueue.end();
         currentAction++)
    {
        (*currentAction)->Reverse();
    }
}



void ActionsQueueTest()
{
    for (actionIter currentAction = particlesActionQueue.begin();
         currentAction != particlesActionQueue.end() ;
         currentAction++)
    {
        (*currentAction)->Perform(gameTimer->GetDelta());
        (*currentAction)->GetActor()->SetLastAction((*currentAction));
    }
    
    for (actionIter currentAction = pelletActionQueue.begin();
         currentAction != pelletActionQueue.end() ;
         currentAction++)
    {
        (*currentAction)->Perform(gameTimer->GetDelta());
        (*currentAction)->GetActor()->SetLastAction((*currentAction));
    }
    
    
    for (actionIter currentAction = playerActionQueue.begin();
         currentAction != playerActionQueue.end() ;
         currentAction++)
    {
        (*currentAction)->Perform(gameTimer->GetDelta());
        (*currentAction)->GetActor()->SetLastAction((*currentAction));
    }
    
}

void CheckForBounds()
{
    for (actorIter curr = particles.begin();
         curr != particles.end();
         curr++)
    {
        Color newColor = (*curr)->GetColor();
        
        int rayPass = rand() % 2;
        
        (*curr)->SetColor(newColor);
        
        if ((*curr)->IsInMotion() &&
            (*curr)->GetDimensions().x <= MAP_WIDTH &&
            (*curr)->GetDimensions().x >= -100 &&
            (*curr)->GetDimensions().y <= MAP_HEIGHT &&
            (*curr)->GetDimensions().y >= -100 &&
            (*curr)->GetID() == PARTICLE_TYPE_RAY
            )
        {
            if (mapSurface !=NULL)
            {
            checkPixel = GetPixel(mapSurface,
                                   (*curr)->GetDimensions().x ,
                                   (*curr)->GetDimensions().y );
            
            mapColor = GetPixelColor(*checkPixel, mapSurface);
            }
           
            if (!SameColor(mapColor, pureWhite))
            {
                // hit solid color
                if (SameColor(mapColor, solidColor) && rayPass != 1)
                {
                    vector<MoveAction*>* list = (*curr)->GetActionList();
                    
                    for (actionIter i = list->begin();
                         i != list->end();
                         i++)
                    {
                        (*i)->Stop();
                    }
                    
                    //Change motion and type when hit occurs
                    (*curr)->SetMotion(false);
                    SetParticleType((*curr), PARTICLE_TYPE_SOLID);
                    
                    //Change color of particle
                    int randomColor = 20 + rand() % 250 + (1 * 10);
                    newColor.red = randomColor - 200;
                    newColor.green = randomColor - 100;
                    newColor.blue = randomColor - 10;
                    
                    newColor.red = (mapColor.r);
                    newColor.green= (mapColor.g);
                    newColor.blue = (mapColor.b);
                    
                    (*curr)->SetColor(newColor);
                }
                
                
                // hit kill color
                if (SameColor(mapColor, redKill) && rayPass!= 1)
                {
                    vector<MoveAction*>* list = (*curr)->GetActionList();
                    
                    for (actionIter i = list->begin();
                         i != list->end();
                         i++)
                    {
                        (*i)->Stop();
                    }
                    
                    //Change motion and type when hit occurs
                    (*curr)->SetMotion(false);
                    SetParticleType((*curr), PARTICLE_TYPE_KILL);
                    
                    //Change color of particle
                    int randomColor = 20 + rand() % 250 + (1 * 10);
                    newColor.red = randomColor - 200;
                    newColor.green = randomColor - 100;
                    newColor.blue = randomColor - 10;
                    
                    newColor.red = (mapColor.r);
                    newColor.green= (mapColor.g);
                    newColor.blue = (mapColor.b);
                    
                    (*curr)->SetColor(newColor);
                }
                
                
                // hit blue pass
                if (SameColor(mapColor, bluePass) && !blueActive && rayPass!= 1)
                {
                    vector<MoveAction*>* list = (*curr)->GetActionList();
                    
                    for (actionIter i = list->begin();
                         i != list->end();
                         i++)
                    {
                        (*i)->Stop();
                    }
                    
                    //Change motion and type when hit occurs
                    (*curr)->SetMotion(false);
                    SetParticleType((*curr), PARTICLE_TYPE_PASSABLE);
                    
                    //Change color of particle
                    int randomColor = 20 + rand() % 250 + (1 * 10);
                    newColor.red = randomColor - 200;
                    newColor.green = randomColor - 100;
                    newColor.blue = randomColor - 10;
                    
                    newColor.red = (mapColor.r);
                    newColor.green= (mapColor.g);
                    newColor.blue = (mapColor.b);
                    
                    (*curr)->SetColor(newColor);
                }
                
                
                // if hit purple and purpke not active make hit
                if (SameColor(mapColor, purplePass) && !purpleActive && rayPass!= 1)
                {
                    vector<MoveAction*>* list = (*curr)->GetActionList();
                    
                    for (actionIter i = list->begin();
                         i != list->end();
                         i++)
                    {
                        (*i)->Stop();
                    }
                    
                    //Change motion and type when hit occurs
                    (*curr)->SetMotion(false);
                    SetParticleType((*curr), PARTICLE_TYPE_PASSABLE);
                    
                    //Change color of particle
                    int randomColor = 20 + rand() % 250 + (1 * 10);
                    newColor.red = randomColor - 200;
                    newColor.green = randomColor - 100;
                    newColor.blue = randomColor - 10;
                    
                    newColor.red = (mapColor.r);
                    newColor.green= (mapColor.g);
                    newColor.blue = (mapColor.b);
                    
                    
                    (*curr)->SetColor(newColor);
                }
                
                
                // if hit yellow and yellow active make hit
                if (SameColor(mapColor, yellowPass) && !yellowActive && rayPass!= 1)
                {
                    vector<MoveAction*>* list = (*curr)->GetActionList();
                    
                    for (actionIter i = list->begin();
                         i != list->end();
                         i++)
                    {
                        (*i)->Stop();
                    }
                    
                    //Change motion and type when hit occurs
                    (*curr)->SetMotion(false);
                    SetParticleType((*curr), PARTICLE_TYPE_PASSABLE);
                    
                    //Change color of particle
                    int randomColor = 20 + rand() % 250 + (1 * 10);
                    newColor.red = randomColor - 200;
                    newColor.green = randomColor - 100;
                    newColor.blue = randomColor - 10;
                    
                    newColor.red = (mapColor.r);
                    newColor.green= (mapColor.g);
                    newColor.blue = (mapColor.b);
                    
                    
                    (*curr)->SetColor(newColor);
                }
                
                
                
                
                // if hit cyan and cyan not active make hit
                if (SameColor(mapColor, cyanPass) && !cyanActive && rayPass !=1)
                {
                    vector<MoveAction*>* list = (*curr)->GetActionList();
                    
                    for (actionIter i = list->begin();
                         i != list->end();
                         i++)
                    {
                        (*i)->Stop();
                    }
                    
                    //Change motion and type when hit occurs
                    (*curr)->SetMotion(false);
                    SetParticleType((*curr), PARTICLE_TYPE_PASSABLE);
                    
                    //Change color of particle
                    int randomColor = 20 + rand() % 250 + (1 * 10);
                    newColor.red = randomColor - 200;
                    newColor.green = randomColor - 100;
                    newColor.blue = randomColor - 10;
                    
                    newColor.red = (mapColor.r);
                    newColor.green= (mapColor.g);
                    newColor.blue = (mapColor.b);
                    
                    
                    (*curr)->SetColor(newColor);
                }
            
            }///end in bounds
        }
        else
        {
            //(*curr)->SetMotion(false);
        }
        
    }
}


void InitSound()
{
    if (!Mix_Init(MIX_INIT_OGG))
    {
        printf("Error initializing sound: %s \n" , Mix_GetError());
    }
}

void OpenAudio()
{
    if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)))
    {
        printf("Error opening audio: %s \n" , Mix_GetError());
    }
    
    Mix_AllocateChannels(1000);
}


void LoadSounds()
{
    s_Blood         = Mix_LoadWAV("teleport.wav");
    s_Bounce        = Mix_LoadWAV("bounce.wav");
    s_Death        = Mix_LoadWAV("death.wav");
    s_Shoot        = Mix_LoadWAV("shoot.wav");
    s_End        = Mix_LoadWAV("warp.wav");
    s_Orb        = Mix_LoadWAV("Orbcollect.wav");
    
    
    s_Song1         = Mix_LoadMUS("/audio/music/song1.ogg");
    
    Mix_VolumeMusic(50);
    
    Mix_VolumeChunk(s_Shoot, 40);
    Mix_VolumeChunk(s_Blood, 20);
    Mix_VolumeChunk(s_Death, 50);
    Mix_VolumeChunk(s_Bounce, 60);
    
    Mix_VolumeChunk(s_End, 30);
    Mix_VolumeChunk(s_Orb, 70);
    
    
    if (!s_Blood)
    {
        printf("Error loading song: %s \n" , Mix_GetError());
    }
    

    
    if (!s_Song1)
    {
        printf("Error loading song: %s \n" , Mix_GetError());
    }
    
    
}


void PlaySound(Mix_Chunk* sound)
{
    for (int i = 0;i <=100;i++) {
        if (!Mix_Playing(i))
        {
            Mix_PlayChannel(i, sound, 0);
            //printf("played channel %i \n" , i);
            break;
        }
    }
}



void TestMusic()
{
    if (Mix_PlayMusic(s_Song1, -1))
    {
        printf("Error playing Music: %s \n" , Mix_GetError());
    }
    
}


void InitTTF()
{
    TTF_Init();
}





void LoadFont()
{
    if (!(f_TestFont = TTF_OpenFont("8bit.ttf", 24)))
    {
        printf("Error loading font %s \n" , TTF_GetError());
    }
}


void RenderText(SDL_Renderer *renderer)
{
    
    SDL_Color color;
    color.r = 100;
    color.g = 100;
    color.b = 100;
    color.a = 200;
    
    textSurface = TTF_RenderText_Solid(f_TestFont, "Hello World", color);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
}


void InitImage()
{
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    printf("Initted %i \n" , initted);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }
}

void LoadImageTest()
{
  

    
}


SDL_Texture* ConvertSurfaceToTexture(SDL_Renderer* renderer, SDL_Surface* surface){
    
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_FreeSurface(surface);
    
    return newTexture;
}



SDL_Color GetPixelColor(Uint32 pixel, SDL_Surface* surface){
    SDL_Color color;
    
    SDL_GetRGB( pixel, surface->format , &color.r, &color.g, &color.b );
    
    return color;
}

Uint8* GetPixel( SDL_Surface *surface, int x, int y )
{
    if (surface != NULL)
    {
    if (x >= surface->w)
    {
        x = surface->w -1;
    }
    
    if (x <= 0)
    {
        x = 0;
    }
    
    
    if (y >= surface->h )
    {
        y =surface->h-1 ;
    }
    
    if (y <= 0)
    {
        y = 0;
    }
    
    //Convert the pixels to 32 bit
    Uint8* pixels = (Uint8*)surface->pixels;
    Uint8* pixel = pixels + y*surface->pitch + x; // offset of pointer
    
    return pixel;
    }
    return 0;
}



RenderableSprite* LoadSprite(RenderableSprite* sprite,string file,SDL_Renderer* sdlRenderer, int w, int h)
{
    SDL_Surface* tempSurface;
    
    tempSurface=IMG_Load(file.c_str());
    if(!tempSurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    //allocate new sprite object
    sprite = new RenderableSprite();

    float x,y;
    Color color;
    
    color.red = 255;
    color.green = 0;
    color.blue = 0;
    
    x = tempSurface->w;
    y = tempSurface->h;
    
    //Convert surface to texture and save to sprite texture object
    sprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, tempSurface));
    
    sprite->SetAngle(0);
    sprite->SetScaleX(1);
    sprite->SetScaleY(1);
    
    SDL_Rect* position = new SDL_Rect;
    
    position->x = 100;
    position->y = 20;
    position->w = w;
    position->h = h;
    
    sprite->SetCenter((x),(y));
    
    sprite->SetColor(color);
    
    sprite->SetSrc(NULL);
    sprite->SetDst(position);
    sprite->SetFlip(SDL_FLIP_NONE);
    
    return sprite;
}



void LoadPlayerSprite(SDL_Renderer* sdlRenderer)
{
    //Load file to surface

    playerSpriteSurface=IMG_Load("greyship.png");
    if(!playerSpriteSurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }
    
    //!!!:REMOVE THIS SHIT
    armSpriteSurface=IMG_Load("cursor.png");
    if(!armSpriteSurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }
    
    cursorSurface=IMG_Load("cursor.png");
    if(!cursorSurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }


    //allocate new sprite object
    playerSprite = new RenderableSprite();
    armSprite    = new RenderableSprite();
    cursorSprite = new RenderableSprite();
    
    float x,y;
    Color color;
    
    color.red = 255;
    color.green = 0;
    color.blue = 0;
    
    x = playerSpriteSurface->w;
    y = playerSpriteSurface->h;
    
    //Convert surface to texture and save to sprite texture object
    playerSprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, playerSpriteSurface));
    

    playerSprite->SetAngle(0);
    playerSprite->SetScaleX(1);
    playerSprite->SetScaleY(1);
    
    SDL_Rect* position = new SDL_Rect;
    
    position->x = 1;
    position->y = 1;
    position->w = playerWidth;
    position->h = playerHeight;
    
    playerSprite->SetCenter((x+16),(y+16));
    
    playerSprite->SetColor(color);
    
    playerSprite->SetSrc(NULL);
    playerSprite->SetDst(position);
    playerSprite->SetFlip(SDL_FLIP_NONE);
    
    
    //Begin arm section-----------------------
    
    color.red = 255;
    color.green = 0;
    color.blue = 0;
    
    x = 0;
    y = 0;
    
    x = armSpriteSurface->w;
    y = armSpriteSurface->h;
    
    //Convert surface to texture and save to sprite texture object
    armSprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, armSpriteSurface));
    
    armSprite->SetCenter(x*-4,y*2);
    
    armSprite->SetAngle(0);
    armSprite->SetScaleX(1);
    armSprite->SetScaleY(1);
    
    position = new SDL_Rect;
    position->x = 100;
    position->y = 20;
    position->w = 40;
    position->h = 40;
    
    armSprite->SetColor(color);
    
    armSprite->SetSrc(NULL);
    armSprite->SetDst(position);
    armSprite->SetFlip(SDL_FLIP_NONE);
    
    
    
    //Begin Cursor section
    color.red = 255;
    color.green = 0;
    color.blue = 0;
    
    x = 0;
    y = 0;
    
    x = cursorSurface->w;
    y = cursorSurface->h;
    
    //Convert surface to texture and save to sprite texture object
    cursorSprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, cursorSurface));
    
    cursorSprite->SetCenter(x*-4,y*2);
    
    cursorSprite->SetAngle(0);
    cursorSprite->SetScaleX(1);
    cursorSprite->SetScaleY(1);
    
    position = new SDL_Rect;
    position->x = 100;
    position->y = 20;
    position->w = 40;
    position->h = 40;
    
    cursorSprite->SetColor(color);
    
    cursorSprite->SetSrc(NULL);
    cursorSprite->SetDst(position);
    cursorSprite->SetFlip(SDL_FLIP_NONE);
    
    
}


Actor* CreateActorAtPos(RenderableSprite* sprite,float x, float y)
{
    Actor* actor = new Actor();
    actor->SetMotion(false);
    
    playerSprite->SetAngle(0);
    
    actor->SetPosX(x);
    actor->SetPosY(y);
    
    actor->SetActorView(sprite);
    
    actor->SetWidth(.5);
    actor->SetHeight(.5);
    
    scrollActors.push_back(actor);
    renderer->AddRenderable(sprite);
    
    return actor;
}


void CreateSpriteAtPos(float x, float y)
{


    playerActor = new Actor();
    playerActor->SetMotion(false);
    playerSprite->SetAngle(0);

    
    playerActor->SetPosX(x);
    playerActor->SetPosY(y);
    
    playerActor->SetActorView(playerSprite);
    
    playerActor->SetWidth(.5);
    playerActor->SetHeight(.5);
    
    
    //begin arm creation
    armActor = new Actor();
    armActor->SetMotion(false);
    armSprite->SetAngle(0);
    

    
    armActor->SetPosX(x);
    armActor->SetPosY(y);
    
    armActor->SetActorView(armSprite);
    
    armActor->SetWidth(.5);
    armActor->SetHeight(.5);
    

    actors.push_back(armActor);
    renderer->AddRenderable(armSprite);
    
    actors.push_back(playerActor);
    renderer->AddRenderable(playerSprite);

}

void PlaceSpriteAt(float x, float y)
{
    SDL_Rect* position = new SDL_Rect;
    
    position->x = x;
    position->y = y;
    
    playerSprite->SetDst(position);
}

void PlaceActorAt(Actor* actor, float x, float y)
{
    dimensions_t position;
    
    position.x = x;
    position.y = y;
    
    actor->GetActorView()->SetDimensions(position);
    
}


void RotateSpriteTowardsPos(float x, float y)
{
    dimensions_t dim1;
    dimensions_t dim2;
    dimensions_t dim3;
    dimensions_t dim4;
    
    dim1.x = x - 60;
    dim1.y = y  - 40;
    
    dim2.x = playerSprite->GetDimensions().x;
    dim2.y = playerSprite->GetDimensions().y;
    
    dim3 = CalculateVectorDifference(dim1, dim2);
    
    dim4 = dim3;
    
    dim4.x*=4;
    dim4.y*=4;
    
    pelletTrajectory = dim4;
    
    double angle = (atan2(dim3.y, dim3.x) * 180 ) / PI ;
    
    armSprite->SetAngle(angle);
    playerSprite->SetAngle(angle);
    
}


dimensions_t CalculateVectorDifference(dimensions_t dim1 , dimensions_t dim2)
{
    dimensions_t finalDim;
    
    if (dim1.x > dim2.x)
    {
        playerSprite->SetFlip(SDL_FLIP_NONE);
        armSprite->SetFlip(SDL_FLIP_NONE);
        
        finalDim.x = dim1.x - dim2.x;
    } else
    {
        //playerSprite->SetFlip(SDL_FLIP_HORIZONTAL);
        //armSprite->SetFlip(SDL_FLIP_VERTICAL);
        finalDim.x = dim2.x - dim1.x;
    }
    

    if (dim1.y > dim2.y)
    {
        finalDim.y = dim1.y - dim2.y;
    } else
    {
        //playerSprite->SetFlip(SDL_FLIP_NONE);
        finalDim.y = dim2.y - dim1.y;
    }

    finalDim.x = dim1.x - dim2.x;
    finalDim.y = dim1.y - dim2.y;
    
    
    return finalDim;
}





//void LoadPelletSprite(SDL_Renderer* sdlRenderer)
//{
//    //Load file to surface
//    pelletSurface=IMG_Load("brightyellowpellet.png");
//    if(!pelletSurface) {
//        printf("IMG_Load: %s\n", IMG_GetError());
//        // handle error
//    }
//
//    //allocate new sprite object
//    pelletSprite = new RenderableSprite();
//    
//    int x,y;
//    
//    Color color;
//    
//    color.red = 255;
//    color.green = 255;
//    color.blue = 255;
//    
//    x = pelletSurface->w;
//    y = pelletSurface->h;
//    
//    //Convert surface to texture and save to sprite texture object
//    pelletSprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, pelletSurface));
//    
//    pelletSprite->SetCenter(x, y);
//    
//    pelletSprite->SetAngle(0);
//    pelletSprite->SetScaleX(1);
//    pelletSprite->SetScaleY(1);
//    
//    SDL_Rect* position = new SDL_Rect;
//    
//    position->x = 100;
//    position->y = 20;
//    position->w = 20;
//    position->h = 20;
//    
//    pelletSprite->SetColor(color);
//    
//    pelletSprite->SetSrc(NULL);
//    pelletSprite->SetDst(position);
//    
//    pelletSprite->SetFlip(SDL_FLIP_NONE);
//}


void CreatePellets(SDL_Renderer* sdlRenderer)
{
    //Create MAX pellets
    for (int i = 0 ; i < PELLETS_MAX  + 10; i++)
    {
        pelletActor = 0;
        pelletActor = new Actor();
        
        pelletSurface=IMG_Load("brightyellowpellet.png");
        if(!pelletSurface) {
            printf("IMG_Load: %s\n", IMG_GetError());
            // handle error
        }
        
        //allocate new sprite object
        pelletSprite = new RenderableSprite();
        
        //Convert surface to texture and save to sprite texture object
        pelletSprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, pelletSurface));
        
        pelletSprite->SetCenter(0, 0);
        
        pelletSprite->SetAngle(0);
        pelletSprite->SetScaleX(1);
        pelletSprite->SetScaleY(1);
        
        SDL_Rect* position = new SDL_Rect;
        
        position->x = -2000;
        position->y = 2000;
        position->w = 30;
        position->h = 30;
        
        Color color;
        
        color.red = 255;
        color.green = 255;
        color.blue = 255;
        
        pelletSprite->SetColor(color);
        
        pelletSprite->SetSrc(NULL);
        pelletSprite->SetDst(position);
        
        pelletSprite->SetFlip(SDL_FLIP_NONE);
        
        pelletActor->SetMotion(false);
        pelletSprite->SetAngle(0);
        
        pelletActor->SetActorView(pelletSprite);
        
        pelletActor->SetWidth(1);
        pelletActor->SetHeight(1);
        
        
        renderer->AddRenderable(pelletSprite);
    
        //Set Trajectory speed as displacement
        dimensions_t displacement;
        dimensions_t targetDisplacement;
        
        targetDisplacement.y =pelletTrajectory.y * .004;
        targetDisplacement.x =pelletTrajectory.x * .004;
    
        pelletActor->SetPosX(-2000);
        pelletActor->SetPosY(2000);
        
        pelletMovement = 0;
        
        pelletMovement = new MoveAction(displacement);
        
        pelletMovement->AttachTo(pelletActor);
        
        pellets.push_back(pelletActor);
        
        pelletActor->AddAction(pelletMovement);
        
        pelletActionQueue.push_back(pelletMovement);
        
        renderer->AddRenderable(pelletSprite);
        
        pelletActor->GetActorView()->SetCameraFollow(false);
    }
}


void ShootPelletFromPlayer()
{
    //Grab new pellet
    actorIter i = pellets.begin() + lastPelletAvailable;
    Actor* pellet = (*i);
    
    //printf("Chose pellet %i ", lastPelletAvailable);
    
    //Set pellet to players position
    pellet->SetPosX(playerActor->GetDimensions().x + 40);
    pellet->SetPosY(playerActor->GetDimensions().y + 40);
    
    
    //Load trajectory displacement
    dimensions_t displacement;
    displacement.y =pelletTrajectory.y * .004;
    displacement.x =pelletTrajectory.x * .004;
    
    ///Check all actions and set to new trajectory
    vector<MoveAction*>* list = pellet->GetActionList();
    
    for (actionIter action = list->begin();
         action != list->end();
         action++)
         {
             (*action)->SetDisplacement(displacement);
             (*action)->Start();
         }
    
    lastPelletAvailable++;
    
    if (lastPelletAvailable>= PELLETS_MAX)
    {
        lastPelletAvailable = 0;
    }
}


//No longer used
void CreatePelletAtPos(float x, float y)
{
    pelletActor = new Actor();
    
    pelletActor->SetMotion(false);
    pelletSprite->SetAngle(0);
    SDL_Rect* position = new SDL_Rect;
    
    position->x = x;
    position->y = y;
    
    pelletActor->SetPosX(x+20);
    pelletActor->SetPosY(y+20);
    
    pelletActor->SetActorView(pelletSprite);
    
    pelletActor->SetWidth(1);
    pelletActor->SetHeight(1);
    
    
    dimensions_t displacement;
    
    displacement.y =pelletTrajectory.y * .004;
    displacement.x =pelletTrajectory.x * .004;
    
    pelletMovement = new MoveAction(displacement);
    
    pelletGravity->AttachTo(pelletActor);
    pelletMovement->AttachTo(pelletActor);
    
    pellets.push_back(pelletActor);

    pelletActionQueue.push_back(pelletMovement);
    
    renderer->AddRenderable(pelletSprite);
    
}


void CheckControls(Uint32 delta)
{
    //THRUSTFORWARD
    if ((buttonUp.held || buttonUp.pressed) && bounceTimer <=0)
    {
        dimensions_t displacement;
        recoilTimer = recoilTime;
        
        //SET MOVE SPEED
        displacement.x = pelletTrajectory.x * .0007;
        displacement.y = pelletTrajectory.y * .0007;
        
        dimensions_t reverseDisp;
        
        reverseDisp.x = -((displacement.x * .03));
        reverseDisp.y = -((displacement.y * .03));
        
        for (actionIter currentAction = particlesActionQueue.begin() + lastParticleAvailable;
             currentAction!= particlesActionQueue.begin() + lastParticleAvailable + numberOfSmokeParticles;
             currentAction++)
        {
            (*currentAction)->SetDisplacement(reverseDisp);
        }
        
        for (actorIter currentActor = particles.begin() + lastParticleAvailable;
             currentActor!= particles.begin() + lastParticleAvailable + numberOfSmokeParticles;
             currentActor++)
        {
            SetParticleType((*currentActor), PARTICLE_TYPE_SMOKE);
        }
        
        
        EjectParticles(playerActor->GetDimensions().x + 32 + cameraX, playerActor->GetDimensions().y + 32 + cameraY, numberOfSmokeParticles);
        
        for (actionIter currentAction = particlesActionQueue.begin() + lastParticleAvailable;
             currentAction!= particlesActionQueue.begin() + lastParticleAvailable + numberOfSmokeParticles;
             currentAction++)
        {
            (*currentAction)->SetDisplacement(reverseDisp);
        }
        
        for (actorIter currentActor = particles.begin() + lastParticleAvailable;
             currentActor!= particles.begin() + lastParticleAvailable + numberOfSmokeParticles;
             currentActor++)
        {
            SetParticleType((*currentActor), PARTICLE_TYPE_SMOKE);
        }
        
        
        EjectParticles(playerActor->GetDimensions().x + 64 + cameraX, playerActor->GetDimensions().y + 64 + cameraY, numberOfSmokeParticles);
        
        
        
        
    
        
        dimensions_t finalDisplacement = playerMoveUp->GetDisplacement();
        
        if (displacement.x > finalDisplacement.x)
        {
            finalDisplacement.x+=moveSpeed * delta;
        }
        
        if (displacement.x < finalDisplacement.x)
        {
            finalDisplacement.x-= moveSpeed * delta;
        }
        
        if (displacement.y > finalDisplacement.y)
        {
            finalDisplacement.y+=moveSpeed * delta;
        }
        
        if (displacement.y < finalDisplacement.y)
        {
            finalDisplacement.y-= moveSpeed * delta;
        }
        
        playerMoveUp->SetDisplacement(finalDisplacement);
        
    } else {
        
        recoilTimer-=gameTimer->GetDelta();
        
        if (recoilTimer <= 0)
        {
            dimensions_t displacement;
            
            displacement = playerMoveUp->GetDisplacement();
            
            displacement.x *= frictionSpeed ;
            displacement.y *= frictionSpeed ;
        
            playerMoveUp->SetDisplacement(displacement);
            recoilTimer = recoilTime;
        }
    }
    
    
    
    
}

void PlaceShipInCenter()
{
    playerActor->SetPosY(100);
    playerActor->SetPosX(100);
}

void CheckScroll()
{
    if (playerActor->GetDimensions().x > SCROLLXRIGHT)
    {
        //printf("Camerax before  %f \n" , cameraX);
        cameraX -= SCROLLXRIGHT - playerActor->GetDimensions().x;
        playerActor->SetPosX(SCROLLXRIGHT);
        //printf("Camerax after  %f \n" , cameraX);

    }
    
        if (playerActor->GetDimensions().x < SCROLLXLEFT)
        {
            cameraX -= SCROLLXLEFT - playerActor->GetDimensions().x ;
            playerActor->SetPosX(SCROLLXLEFT);
        }
        

        if (playerActor->GetDimensions().y > SCROLLYBOTTOM)
        {
            cameraY -= SCROLLYBOTTOM - playerActor->GetDimensions().y ;
            playerActor->SetPosY(SCROLLYBOTTOM);
        }
        
        
        if (playerActor->GetDimensions().y < SCROLLYTOP)
        {
            cameraY -= SCROLLYTOP - playerActor->GetDimensions().y ;
            playerActor->SetPosY(SCROLLYTOP);
        }
}

void CheckShoot()
{
    shotTimer-= gameTimer->GetDelta();
    if (shotTimer <=0)
    {
        shotTimer = 0;
    }
    if (GAME_STATE == LEVEL && (buttonNext.held || buttonNext.pressed) && shotTimer <=0){
        shotTimer = shotTime;
        PlaySound(s_Shoot);
        ShootPelletFromPlayer();
    }
}

void CheckPelletCollision()
{
    
    
    if (mapSurface !=NULL)
    {
        //Check all pellets for collision
        for (actorIter i = pellets.begin();
             i != pellets.end();
             i++)
        {
            
            if ((*i)->GetDimensions().x < MAP_WIDTH &&
                (*i)->GetDimensions().x > -MAP_WIDTH &&
                (*i)->GetDimensions().y < MAP_HEIGHT &&
                (*i)->GetDimensions().y > -MAP_HEIGHT
                )
            {
                Actor* pellet = (*i);
                checkPixel = GetPixel(mapSurface,
                                      pellet->GetDimensions().x + cameraX,
                                      pellet->GetDimensions().y + cameraY);
                mapColor = GetPixelColor(*checkPixel, mapSurface);
                
                //hit something
                if (!SameColor(mapColor, pureWhite))
                {
                    //check standard solid
                    if (SameColor(mapColor, solidColor))
                    {
                        CastRaysFromPellet(pellet);
                    }
                    //check kill
                    if (SameColor(mapColor, redKill))
                    {
                        CastRaysFromPellet(pellet);
                    }
                    
                    //check blue , if not active then explode
                    if (SameColor(mapColor, bluePass) && !blueActive)
                    {
                        CastRaysFromPellet(pellet);
                    }
                    
                    //check yellow, if not active then explode pellet
                    if (SameColor(mapColor, yellowPass) && !yellowActive)
                    {
                        CastRaysFromPellet(pellet);
                    }
                
                    
                    //check purple, if not active then explode pellet
                    if (SameColor(mapColor, purplePass) && !purpleActive)
                    {
                        CastRaysFromPellet(pellet);
                    }
                    
                    //check cyan, if not active then explode pellet
                    if (SameColor(mapColor, cyanPass) && !cyanActive)
                    {
                        CastRaysFromPellet(pellet);
                    }
                }
            }
        }
    }
}



void CastRaysFromPellet(Actor* pellet)
{
     pellet->GetLastAction()->Undo(gameTimer->GetDelta());
        
        //Choose X amount of particles to repurpose
        for (actorIter i = particles.begin() + lastParticleAvailable;
             i!=particles.begin() + lastParticleAvailable + totalParticlesPerCast;
             i++
             )
        {
            SetParticleType((*i), PARTICLE_TYPE_RAY);
        
            ActionList list = (*i)->GetActionList();
            
            for (actionIter currentAction = list->begin();
                 currentAction != list->end();
                 currentAction++)
            {
                dimensions_t tempDisplacement;
                
                //Set action
                float xSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
                //printf("X speed: %f \n", xSpeed) ;
                //float finalXSpeed = xSpeed + (rand() % 1);
                float finalXSpeed = xSpeed /1;
                
                float ySpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
                //float finalYSpeed = ySpeed + (rand() % 1);
                float finalYSpeed =  ySpeed *2;
                
                bool flipVert,flipHor;
                
                flipVert = rand() % 3;
                flipHor = rand() % 3;
                
                
                if (flipVert)
                {
                    tempDisplacement.y = -finalYSpeed;
                } else
                {
                    tempDisplacement.y = finalYSpeed;
                }
                
                if (flipHor)
                {
                    tempDisplacement.x = -finalXSpeed;
                } else
                {
                    tempDisplacement.x = finalXSpeed;
                }
            
                (*currentAction)->SetDisplacement(tempDisplacement);
            }
        }
    
    
    EjectParticles(pellet->GetDimensions().x +cameraX + ejectDirection.x, pellet->GetDimensions().y + cameraY + ejectDirection.y, totalParticlesPerCast);
    
    PlaySound(s_Blood);
    
    DeletePellet(pellet);
}


//Moves pellet off screen and stops movement
void DeletePellet(Actor* pellet)
{
    pellet->SetPosY(100000);
    pellet->SetPosX(100000);
   
    vector<MoveAction*>* list = pellet->GetActionList();
    
    for (actionIter i = list->begin();
         i != list->end();
         i++)
    {
        (*i)->Stop();
    }

}


void CalculateEjectDirection()
{
//    if (pelletActor){
//    ejectDirection.x = pelletMovement->GetDisplacement().x + pelletGravity->GetDisplacement().x;
//    ejectDirection.y = pelletMovement->GetDisplacement().y + pelletGravity->GetDisplacement().y;
//    }
}


void PlaceCannonOnPlayer()
{
    armActor->SetPosX(2000);
    armActor->SetPosY(2000);
}

void SetCamera()
{
    //printf("2nd: Set to x %f y %f \n" ,cameraX , cameraY);
    
    for(actorIter i = particles.begin();
        i !=particles.end();
        i++
        )
    {
        (*i)->GetActorView()->SetCameraX(cameraX);
        (*i)->GetActorView()->SetCameraY(cameraY);
    }
    
    for(actorIter i = pellets.begin();
        i !=pellets.end();
        i++
        )
    {
        (*i)->GetActorView()->SetCameraX(cameraX);
        (*i)->GetActorView()->SetCameraY(cameraY);
    }
    
    
    for(actorIter i = scrollActors.begin();
        i !=scrollActors.end();
        i++
        )
    {
        (*i)->GetActorView()->SetCameraX(cameraX);
        (*i)->GetActorView()->SetCameraY(cameraY);
    }

    
}

void ChangeFullScreen(bool fullscreen)
{
    int flags;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    } else
    {
        flags = SDL_WINDOW_SHOWN;
    }
    
    SDL_SetWindowFullscreen(win,flags);

}



void PrintDynamicMemory()
{
    printf("Delta: %u \n" , gameTimer->GetDelta());
    
    printf("size of actors queue: %lu \n" , actors.size());
    printf("size of particles actor queue: %lu \n" , particles.size());
    
        printf("size of pellets actor queue: %lu \n" , pellets.size());
    
    printf("size of particles action queue: %lu \n" , particlesActionQueue.size());
    printf("size of player action queue: %lu \n" , playerActionQueue.size());
    printf("size of pellet action queue: %lu \n" , pelletActionQueue.size());
    
    printf("size of renderables queue: %lu \n" , renderer->GetRenderablesSize());

}


void SetCameraTo(float x, float y)
{
    //printf("Set to x %f y %f \n" ,x , y);
    cameraX = x;
    cameraY = y;
    SetCamera();
}


void SetMapColorKey()
{
    //invisibles
    pureWhite.r = 255;
    pureWhite.b = 255;
    pureWhite.g = 255;
    
    offWhite.r = 0xFE;
    offWhite.g = 0xFE;
    offWhite.b = 0xFE;

    
    //Solid blocks
    solidColor.r = 100;
    solidColor.g = 100;
    solidColor.b = 100;
    
    //Passables
    bluePass.r = 0;
    bluePass.g = 0;
    bluePass.b = 100;

    //Key passables
    greenPass.r = 0;
    greenPass.g = 100;
    greenPass.b = 0;
    
    yellowPass.r = 100;
    yellowPass.g = 100;
    yellowPass.b = 0;
    
    purplePass.r = 100;
    purplePass.g = 0;
    purplePass.b = 100;
    
    cyanPass.r = 0;
    cyanPass.g = 100;
    cyanPass.b = 100;
    
    
    
    //Kill block
    redKill.r = 100;
    redKill.g = 0;
    redKill.b = 0;
    
    
    //Spawnables
    startColor.r = 50;
    startColor.g = 50;
    startColor.b = 50;
    
    endColor.r = 200;
    endColor.g = 200;
    endColor.b = 200;
    
    enemyColor.r = 200;
    enemyColor.g = 0;
    enemyColor.b = 0;
    
    //Key spawns
    yellowKeyColor.r = 200;
    yellowKeyColor.g = 200;
    yellowKeyColor.b = 0;
    
    
    purpleKeyColor.r = 200;
    purpleKeyColor.g = 0;
    purpleKeyColor.b = 200;
    
    cyanKeyColor.r = 0;
    cyanKeyColor.g = 200;
    cyanKeyColor.b = 200;
    
    greenKeyColor.r = 0;
    greenKeyColor.g = 200;
    greenKeyColor.b = 0;
    
    //Orb spawns
    yellowOrbColor.r = 50;
    yellowOrbColor.g = 50;
    yellowOrbColor.b = 0;
    
    greenOrbColor.r = 0;
    greenOrbColor.g = 50;
    greenOrbColor.b = 0;
    
    purpleOrbColor.r = 50;
    purpleOrbColor.g = 0;
    purpleOrbColor.b = 50;
    
    cyanOrbColor.r = 0;
    cyanOrbColor.g = 50;
    cyanOrbColor.b = 50;
    
}





void CreatePlayerActions()
{
    dimensions_t displacement;
    displacement.x = 0;
    displacement.y = 0;
    
    //Begin Movement actions
    //playerMoveRight = new MoveAction(displacement);
    //playerMoveLeft = new MoveAction(displacement);
    playerMoveUp = new MoveAction(displacement);
    //playerMoveDown = new MoveAction(displacement);
    
    //playerMoveRight->AttachTo(playerActor);
    //playerMoveLeft->AttachTo(playerActor);
    //playerMoveDown->AttachTo(playerActor);
    playerMoveUp->AttachTo(playerActor);
    
    //playerActionQueue.push_back(playerMoveRight);
    //playerActionQueue.push_back(playerMoveLeft);
    //playerActionQueue.push_back(playerMoveDown);
    playerActionQueue.push_back(playerMoveUp);
    
}





bool SameColor(SDL_Color color1 , SDL_Color color2)
{
    if (color1.r == color2.r &&
        color1.g == color2.g &&
        color1.b == color2.b
        )
    {
        return true;
    }
    
    return false;
}




void UpdateParticles(Uint32 delta)
{
    Color newColor;
    
    particleTimerFast-= particleFadeTimeFast * delta;
    particleTimerSlow-= particleFadeTimeSlow * delta;
    particleTimerMedium-= particleFadeTimeMedium * delta;
    
    //printf("Particle TF:%i , TM:%i , TS:%i \n" , particleTimerFast, particleTimerMedium, particleTimerSlow);
    
    //Check particles for style
    for (actorIter i = particles.begin();
         i != particles.end();
         i++)
    {
        newColor = (*i)->GetColor();
        
        switch ((*i)->GetID())
        {
            case PARTICLE_TYPE_PERMANENT:
                break;
                
                
            case PARTICLE_TYPE_EXPLOSION:
                if (particleTimerFast <=0)
                {
                    newColor.red -= 1;
                    newColor.green -= 2;
                    newColor.blue -= 2;
                }
                //Stop at bottom of color
                if (newColor.red <= 0){newColor.red = 0;}
                if (newColor.green <= 0){newColor.green = 0;}
                if (newColor.blue <= 0){newColor.blue = 0;}
                
                if (newColor.red == 0 &&
                    newColor.blue == 0 &&
                    newColor.green == 0)
                {
                    PlaceParticleAt((*i), 2000, 2000);
                }
                (*i)->SetColor(newColor);
                break;
                
            case PARTICLE_TYPE_WARP:
                if (particleTimerFast <=0)
                {
                    newColor.red -= 1 ;
                    newColor.green -= 1;
                    newColor.blue -= 1;
                }
                //Stop at bottom of color
                if (newColor.red <= 0){newColor.red = 0;}
                if (newColor.green <= 0){newColor.green = 0;}
                if (newColor.blue <= 0){newColor.blue = 0;}
                
                if (newColor.red == 0 &&
                    newColor.blue == 0 &&
                    newColor.green == 0)
                {
                    PlaceParticleAt((*i), 2000, 2000);
                }
                (*i)->SetColor(newColor);
                break;
                
                
            case PARTICLE_TYPE_SMOKE:
                if (particleTimerFast <=0)
                {
                    newColor.red -= 2;
                    newColor.green -= 2;
                    newColor.blue -= 2;
                }
                //Stop at bottom of color
                if (newColor.red <= 0){newColor.red = 0;}
                if (newColor.green <= 0){newColor.green = 0;}
                if (newColor.blue <= 0){newColor.blue = 0;}
                
                if (newColor.red == 0 &&
                    newColor.blue == 0 &&
                    newColor.green == 0)
                {
                    PlaceParticleAt((*i), 2000, 2000);
                }
                (*i)->SetColor(newColor);
                break;
                
            case PARTICLE_TYPE_GUNSHOT:
                if (particleTimerFast <=0)
                {
                    newColor.red -= 2;
                    newColor.green -= 2;
                    newColor.blue -= 2;
                }
                //Stop at bottom of color
                if (newColor.red <= 0){newColor.red = 0;}
                if (newColor.green <= 0){newColor.green = 0;}
                if (newColor.blue <= 0){newColor.blue = 0;}
                
                if (newColor.red == 0 &&
                    newColor.blue == 0 &&
                    newColor.green == 0)
                {
                    PlaceParticleAt((*i), 2000, 2000);
                }
                (*i)->SetColor(newColor);
                break;
                
                
                
            case PARTICLE_TYPE_INVISIBLE:
                newColor.red -= 3;
                newColor.blue -= 3;
                newColor.green -= 3;
                
                if (newColor.red <= 0){newColor.red = 0;}
                if (newColor.green <= 0){newColor.green = 0;}
                if (newColor.blue <= 0){newColor.blue = 0;}
        
                if (newColor.red == 0 &&
                    newColor.blue == 0 &&
                    newColor.green == 0)
                {
                    PlaceParticleAt((*i), 2000, 2000);
                }
                (*i)->SetColor(newColor);
                break;
                
            case PARTICLE_TYPE_RAY:
                if (particleTimerFast<=0)
                {
                    switch (currentPower) {
                        case bluePower:
                            newColor.red = 50;
                            newColor.green = 50;
                            newColor.blue -= 20;
                            break;
                        
                        case yellowPower:
                            newColor.red = 50;
                            newColor.green =50;
                            newColor.blue = 0;
                            break;
                            
                        case cyanPower:
                            newColor.red = 0;
                            newColor.green = 50;
                            newColor.blue = 50;
                            break;
                            
                        case purplePower:
                            newColor.red = 50;
                            newColor.green =0  ;
                            newColor.blue = 50;
                            break;
                            
                        case noPower:
                            newColor.red += 5;
                            newColor.green +=5 ;
                            newColor.blue += 5;
                            break;
                            
                            
                            
                        default:
                            break;
                    }
                }
                (*i)->SetColor(newColor);
                break;
                
                
            case PARTICLE_TYPE_CORRUPT:
                newColor.red -= 10;
                newColor.green += 1;
                newColor.blue += 1;
                (*i)->SetColor(newColor);
                break;
                
            case PARTICLE_TYPE_SOLID:
                //Medium speed solid
                if (particleTimerFast <=0)
                {
                    newColor.red -= 1;
                    newColor.green -= 1;
                    newColor.blue -= 1;
                }
                //Stop at bottom of color
                if (newColor.red <= 0){newColor.red = 0;}
                if (newColor.green <= 0){newColor.green = 0;}
                if (newColor.blue <= 0){newColor.blue = 0;}
                
                if (newColor.red == 0 &&
                    newColor.blue == 0 &&
                    newColor.green == 0)
                {
                    PlaceParticleAt((*i), 2000, 2000);
                }
                
                (*i)->SetColor(newColor);
                break;
                
                
            case PARTICLE_TYPE_PASSABLE:
                //Fast  Passable type
                if (particleTimerMedium <=0)
                {
                    newColor.red -= 1;
                    newColor.green -= 1;
                    newColor.blue -= 1;
                }
                //Stop at bottom of color
                if (newColor.red <= 0){newColor.red = 0;}
                if (newColor.green <= 0){newColor.green = 0;}
                if (newColor.blue <= 0){newColor.blue = 0;}
                
                if (newColor.red == 0 &&
                    newColor.blue == 0 &&
                    newColor.green == 0)
                {
                    PlaceParticleAt((*i), 2000, 2000);
                }
                
                (*i)->SetColor(newColor);
                break;
                
            case PARTICLE_TYPE_KILL:
                //Slow kill type
                if (particleTimerSlow <=0)
                {
                    newColor.red -= 900;
                    newColor.green -= 1;
                    newColor.blue += 1;
                }
                //Stop at bottom of color
               // if (newColor.red <= 0){newColor.red = 0;}
                if (newColor.green <= 0){newColor.green = 0;}
                if (newColor.blue <= 0){newColor.blue = 0;}
                
                if (newColor.red == 40 &&
                    newColor.blue == 0 &&
                    newColor.green == 0)
                {
                    PlaceParticleAt((*i), 2000, 2000);
                }
                
                (*i)->SetColor(newColor);
                break;
                
            default:
                break;
        }
    }
    
    if (particleTimerSlow <=0){particleTimerSlow = particleTime;}
    if (particleTimerMedium <=0){particleTimerMedium = particleTime;}
    if (particleTimerFast <=0){particleTimerFast = particleTime;}
}


void SetParticleType(Actor* particle, particle_type type)
{
    particle->SetID(type);
    
    int randX = 1 +rand() % 1;
    int randY = 1 + rand() % 1;
    
    randX = 0;
    randY = 0;

    
    int randomColor = 1 + rand() % 30 + (1 * 10);
    
    float xSpeed,ySpeed;
    float finalXSpeed,finalYSpeed;
    bool flipVert,flipHor;
    dimensions_t tempDisplacement;
    Color newColor;
    
    switch (particle->GetID()) {
            
        case PARTICLE_TYPE_INVISIBLE:
            break;
            
        case PARTICLE_TYPE_RAY:
            newColor.red = randomColor + 30;
            newColor.green = randomColor + 44;
            newColor.blue = randomColor + 50;
            
            xSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
            //printf("X speed: %f \n", xSpeed) ;
            //float finalXSpeed = xSpeed + (rand() % 1);
            finalXSpeed =0 + xSpeed *2;
            
            ySpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
            //float finalYSpeed = ySpeed + (rand() % 1);
            finalYSpeed = 0 +  ySpeed *2;
            
            flipVert = rand() % 3;
            flipHor = rand() % 3;
            
            
            if (flipVert)
            {
                tempDisplacement.y = -finalYSpeed;
            } else
            {
                tempDisplacement.y = finalYSpeed;
            }
            
            if (flipHor)
            {
                tempDisplacement.x = -finalXSpeed;
            } else
            {
                tempDisplacement.x = finalXSpeed;
            }
            particle->GetLastAction()->SetDisplacement(tempDisplacement);
            
            break;
            
        case PARTICLE_TYPE_SMOKE:
            newColor.red = 100;
            newColor.green = 70;
            newColor.blue = 70;
            break;
            
        case PARTICLE_TYPE_GUNSHOT:
            newColor.red = 255;
            newColor.green = 255;
            newColor.blue = 255;
            break;
            
        case PARTICLE_TYPE_WARP:
            newColor.red = 100;
            newColor.green = 150;
            newColor.blue = 255;
            
            xSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
            //printf("X speed: %f \n", xSpeed) ;
            //float finalXSpeed = xSpeed + (rand() % 1);
            finalXSpeed =0 + xSpeed *2;
            
            ySpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
            //float finalYSpeed = ySpeed + (rand() % 1);
            finalYSpeed = 0 +  ySpeed *2;
            
            flipVert = rand() % 3;
            flipHor = rand() % 3;
            
            
            if (flipVert)
            {
                tempDisplacement.y = -finalYSpeed;
            } else
            {
                tempDisplacement.y = finalYSpeed;
            }
            
            if (flipHor)
            {
                tempDisplacement.x = -finalXSpeed;
            } else
            {
                tempDisplacement.x = finalXSpeed;
            }
            particle->GetLastAction()->SetDisplacement(tempDisplacement);
            break;
            
        case PARTICLE_TYPE_EXPLOSION:
            newColor.red = 200;
            newColor.green = 100;
            newColor.blue = 100;
            
            xSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
            //printf("X speed: %f \n", xSpeed) ;
            //float finalXSpeed = xSpeed + (rand() % 1);
            finalXSpeed =0 + xSpeed *2;
            
            ySpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
            //float finalYSpeed = ySpeed + (rand() % 1);
            finalYSpeed = 0 +  ySpeed *2;
            
            flipVert = rand() % 3;
            flipHor = rand() % 3;
            
            
            if (flipVert)
            {
                tempDisplacement.y = -finalYSpeed;
            } else
            {
                tempDisplacement.y = finalYSpeed;
            }
            
            if (flipHor)
            {
                tempDisplacement.x = -finalXSpeed;
            } else
            {
                tempDisplacement.x = finalXSpeed;
            }
            particle->GetLastAction()->SetDisplacement(tempDisplacement);
            break;
            
            
            
        default:
            break;
    }
}


//Only use to rotate in a circle for set_center tests
void RotateSprite()
{
    circleAngle++;
    playerSprite->SetAngle(circleAngle);
}


void PrintCameraPos()
{
    printf("Camera X: %f , Camera Y:%f \n" , cameraX, cameraY);
}


void CreateParticlesAt(int num,float x, float y)
{
    srand(static_cast <unsigned int>(time(0)));
    
    Color newColor;
    MoveAction* newMove;
    dimensions_t tempDisplacement;
    
    newColor.red = 0;
    newColor.blue = 0;
    newColor.green = 0;
    newColor.alpha = 0;
    
    //Create particle objects
    for (int i = 0 ; i < num ; i++)
    {
        particle = NULL;
        particle = new Actor();
        
        particle->SetMotion(true);
        
        particleShape    = 0;
        particleShape    = new RenderableShape();
        particleShape->SetCameraFollow(true);
        float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float finalRandom = random + (rand() % 20);
        
        particle->SetWidth(finalRandom/2);
        particle->SetHeight(finalRandom/2);
        
        
        random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        finalRandom = (rand() % 1) + random + (rand() % 1 );
        finalRandom = 0;
        
        particle->SetPosX(x);
        particle->SetPosY(y);
        
        particle->SetColor(newColor);
        
        
        //Set action
        float xSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
        //printf("X speed: %f \n", xSpeed) ;
        //float finalXSpeed = xSpeed + (rand() % 1);
        float finalXSpeed = xSpeed /1;
        
        float ySpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/1;
        //float finalYSpeed = ySpeed + (rand() % 1);
        float finalYSpeed =  ySpeed *2;
        
        bool flipVert,flipHor;
        
        flipVert = rand() % 3;
        flipHor = rand() % 3;
        
        
        if (flipVert)
        {
            tempDisplacement.y = -finalYSpeed;
        } else
        {
            tempDisplacement.y = finalYSpeed;
        }
        
        if (flipHor)
        {
            tempDisplacement.x = -finalXSpeed;
        } else
        {
            tempDisplacement.x = finalXSpeed;
        }
        
        newMove = new MoveAction(tempDisplacement);
        
        newMove->AttachTo(particle);
        particlesActionQueue.push_back(newMove);
        newMove->Stop();
        particle->AddAction(newMove);
        
        
        
        //Connect actor to view object
        particle->SetActorView(particleShape);
        //Add view object to renderer
        renderer->AddRenderable(particle->GetActorView());
        particles.push_back(particle);
    }
}


vector<Actor*>::iterator DeleteParticle(Actor* deadParticle)
{
    for (actorIter i = particles.begin();
         i != particles.end();
         i++
         )
    {
        if ((*i) == deadParticle)
        {
            delete deadParticle;
            return particles.erase(i);
        }
    }
    return particles.end();
}



void PlaceParticleAt(Actor* particle, float x, float y)
{
    particle->SetPosX(x);
    particle->SetPosY(y);
}



void MoveAim()
{
    
    if (aimX < lastMouseX - 40)
    {
        aimX+=aimTurnSpeed * gameTimer->GetDelta() ;
    }
    
    if (aimX > lastMouseX - 40)
    {
        aimX-=aimTurnSpeed * gameTimer->GetDelta();
    }
    
    if (aimY < lastMouseY - 40)
    {
        aimY+=aimTurnSpeed * gameTimer->GetDelta();
    }
    
    if (aimY > lastMouseY - 40)
    {
        aimY-=aimTurnSpeed * gameTimer->GetDelta();
    }
    
    //printf("Aimx %f AImy %i \n " , aimX, aimY);
    
}


    

void CreatePortal(SDL_Renderer* sdlRenderer)
{
  
                SDL_Rect* position = new SDL_Rect;
                
                portalSurface=IMG_Load("endspiral.png");
                if(!portalSurface) {
                    printf("IMG_Load: %s\n", IMG_GetError());
                    // handle error
                }
                
                portalSprite = new RenderableSprite();

                Color color;
               
                color.red = 255;
                color.green = 0;
                color.blue = 0;
                
                //Convert surface to texture and save to sprite texture object
                portalSprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, portalSurface));
                
                portalSprite->SetAngle(0);
                portalSprite->SetScaleX(1);
                portalSprite->SetScaleY(1);
                
                position->x = 0;
                position->y = 0;
                position->w = 250;
                position->h = 250;
                
                portalSprite->SetCenter(0,0);
                
                portalSprite->SetColor(color);
                
                portalSprite->SetSrc(NULL);
                portalSprite->SetDst(position);
                portalSprite->SetFlip(SDL_FLIP_NONE);
                
            
                portalActor = new Actor();
                portalActor->SetMotion(false);
                portalSprite->SetAngle(0);
                
                position->x = 0;
                position->y = 0;
                
                portalActor->SetPosX(0);
                portalActor->SetPosY(0);
                
                portalActor->SetActorView(portalSprite);
                
                portalActor->SetWidth(.5);
                portalActor->SetHeight(.5);
                
                scrollActors.push_back(portalActor);
                renderer->AddRenderable(portalSprite);
                
                portalActor->GetActorView()->SetCameraFollow(true);
            }


void LoadSpawnPoint()
{
    playerActor->SetPosX(SCREEN_WIDTH/2);
    playerActor->SetPosY(SCREEN_HEIGHT/2);
    
    
    playerMoveUp->Stop();
    
    for (int x = 0 ; x < mapSurface->w ; x++)
    {
        for (int y = 0; y < mapSurface->h; y++)
        {
            checkPixel = GetPixel(mapSurface,x,y);
            
            mapColor = GetPixelColor(*checkPixel, mapSurface);
            
            if (SameColor(mapColor,startColor))
            {
        
                //spawnPoint.x = x - SCREEN_WIDTH/2 - playerWidth/8 - 2548;
                //spawnPoint.y = y - SCREEN_HEIGHT/2 - playerHeight/8  - 2666;

                spawnPoint.x = x - SCREEN_WIDTH/2 + SCROLLDEADZONEX - 32;
                spawnPoint.y = y - SCREEN_HEIGHT/2  + SCROLLDEADZONEY - 32;
                
                //printf("found spawn at: x %f y %f ", spawnPoint.x , spawnPoint.y);
                
                SetCameraTo(spawnPoint.x,spawnPoint.y);
                
                //SetCameraTo(670,1500);
                
//                SetCameraTo(x - SCREEN_WIDTH/2 - playerWidth/8, y - SCREEN_HEIGHT/2 - playerHeight/8);
            }
        }
    }
}



void CheckActivePower()
{
    switch (currentPower) {
            
        case bluePower:
            blueActive = true;
            yellowActive = false;
            neutralActive = false;
            purpleActive = false;
            cyanActive = false;
            break;
            
        case yellowPower:
            if (!yellowKey)
            {
                currentPower++;
            }
            blueActive = false;
            yellowActive = true;
            neutralActive = false;
            purpleActive = false;
            cyanActive = false;
            break;
            
        case purplePower:
            if (!purpleKey)
            {
                currentPower++;
            }
            blueActive = false;
            yellowActive = false;
            neutralActive = false;
            purpleActive = true;
            cyanActive = false;
            break;
            
        case cyanPower:
            if (!cyanKey)
            {
                currentPower++;
            }
            blueActive = false;
            yellowActive = false;
            neutralActive = false;
            purpleActive = false;
            cyanActive = true;
            break;
            
            
        case noPower:
            blueActive = false;
            yellowActive = false;
            neutralActive = true;
            purpleActive = false;
            cyanActive = false;
            break;
        
            
        case allPower:
            if (!allKey)
            {
                currentPower = noPower;
            }
            blueActive = true;
            yellowActive = true;
            neutralActive = true;
            purpleActive = true;
            cyanActive = true;
            break;
            
            
            
        default:
            break;
    }
    
    if (currentPower > cyanPower){
        currentPower = noPower;
    }
}


void PlaceOrbsAroundShip()
{
    if (blueActive){
        blueOrbActor->SetPosX(playerActor->GetDimensions().x - 32);
        blueOrbActor->SetPosY(playerActor->GetDimensions().y - 32);
    } else {
        blueOrbActor->SetPosY(1000);
    }
    
    if (yellowActive){
        yellowOrbActor->SetPosX(playerActor->GetDimensions().x - 32);
        yellowOrbActor->SetPosY(playerActor->GetDimensions().y- 32);
    } else {
        yellowOrbActor->SetPosY(1000);
    }
    
    if (cyanActive){
        cyanOrbActor->SetPosX(playerActor->GetDimensions().x - 32);
        cyanOrbActor->SetPosY(playerActor->GetDimensions().y- 32);
    } else {
        cyanOrbActor->SetPosY(1000);
    }
    
    
    if (purpleActive){
        purpleOrbActor->SetPosX(playerActor->GetDimensions().x - 32);
        purpleOrbActor->SetPosY(playerActor->GetDimensions().y- 32);
    } else {
        purpleOrbActor->SetPosY(1000);
    }
}


void CheckShipCollision()
{
    bounceTimer-= gameTimer->GetDelta();
    
    if (bounceTimer <=0)
    {
        bounceTimer = 0;
    }
    
    //printf(" bouncertimer: %i \n" , bounceTimer);
    
    if (DidCollide(playerSprite, portalSprite))
    {
        printf("hit portal \n");
        PlaySound(s_End);
        PlayerWin();
    }
    
    
    if (DidCollide(playerSprite, yellowKeySprite))
    {
        printf("hit yellow key! \n");
        dimensions_t dim ;
        dim.x = -10000;
        dim.y = 100000;
        yellowKeySprite->SetDimensions(dim);
        yellowKey = true;
        currentPower = yellowPower;
        PlaySound(s_Orb);
        
    }
    
    if (DidCollide(playerSprite, cyanKeySprite))
    {
        printf("hit cyan key! \n");
        dimensions_t dim ;
        dim.x = -10000;
        dim.y = 100000;
        cyanKeySprite->SetDimensions(dim);
        cyanKey = true;
        currentPower = cyanPower;
        PlaySound(s_Orb);
    }
    
    if (DidCollide(playerSprite, purpleKeySprite))
    {
        printf("hit purple key! \n");
        dimensions_t dim ;
        dim.x = -10000;
        dim.y = 100000;
        purpleKeySprite->SetDimensions(dim);
        purpleKey = true;
        currentPower = purplePower;
        PlaySound(s_Orb);
    }
    
    dimensions_t displacement;

    if (mapSurface !=NULL)
    {
        bool keepChecking = true;
        onColor = false;
        //Grab color
        for (int x = playerWidth/8 ; x < playerWidth - playerWidth/8 ; x++)
        {
            for (int y = playerHeight/8  ; y < playerHeight - playerHeight/8 ; y++)
            {
                if (keepChecking && bounceTimer <=0)
                {
                checkPixel = GetPixel(mapSurface,
                                      (playerActor->GetDimensions().x) + x + cameraX,
                                      (playerActor->GetDimensions().y) + y + cameraY);
                
                mapColor = GetPixelColor(*checkPixel, mapSurface);
                
                
                if (!SameColor(mapColor, pureWhite))
                {
                    //onColor = true;
                    //printf("on color \n") ;
                }
                    
                //hit kill wall
                if (SameColor(mapColor, redKill))
                {
                    keepChecking = false;
                    bounceTimer = bounceTime;
                    PlayerKill();
                }
                
                    //hit solid
                    if (SameColor(mapColor, solidColor)&& bounceTimer <=0)
                    {
                        keepChecking = false;
                       displacement = playerActor->GetLastAction()->GetDisplacement();
                        
                        displacement.x*=bounceRecoil;
                        displacement.y*=bounceRecoil;
                        
                        playerMoveUp->SetDisplacement(displacement);
                        playerMoveUp->Undo(gameTimer->GetDelta());

                        bounceTimer = bounceTime;
                        PlaySound(s_Bounce);
                    }
                    
                    //hit blue when not active
                    if (SameColor(mapColor, bluePass) && !blueActive)
                    {
                        keepChecking = false;
                        displacement = playerActor->GetLastAction()->GetDisplacement();
                        
                        displacement.x*=bounceRecoil;
                        displacement.y*=bounceRecoil;
                        
                        playerMoveUp->SetDisplacement(displacement);
                        playerMoveUp->Undo(gameTimer->GetDelta());
                        bounceTimer = bounceTime;
                        PlaySound(s_Bounce);
                    }
                    
                //hit yellow when not active
                if (SameColor(mapColor, yellowPass) && !yellowActive)
                {
                    keepChecking = false;
                    displacement = playerActor->GetLastAction()->GetDisplacement();
                    
                    displacement.x*=bounceRecoil;
                    displacement.y*=bounceRecoil;
                    
                    playerMoveUp->SetDisplacement(displacement);
                    playerMoveUp->Undo(gameTimer->GetDelta());
                    bounceTimer = bounceTime;
                    PlaySound(s_Bounce);
                }
                
                //hit blue when not active
                if (SameColor(mapColor, cyanPass) && !cyanActive)
                {
                    keepChecking = false;
                    displacement = playerActor->GetLastAction()->GetDisplacement();
                    
                    displacement.x*=bounceRecoil;
                    displacement.y*=bounceRecoil;
                    
                    playerMoveUp->SetDisplacement(displacement);
                    playerMoveUp->Undo(gameTimer->GetDelta());
                    bounceTimer = bounceTime;
                    PlaySound(s_Bounce);
                }
                
                //hit blue when not active
                if (SameColor(mapColor, purplePass) && !purpleActive)
                {
                    keepChecking = false;
                    displacement = playerActor->GetLastAction()->GetDisplacement();
                    
                    displacement.x*=bounceRecoil;
                    displacement.y*=bounceRecoil;
                    
                    playerMoveUp->SetDisplacement(displacement);
                    playerMoveUp->Undo(gameTimer->GetDelta());
                    bounceTimer = bounceTime;
                    PlaySound(s_Bounce);
                }
                }
            }
        }
    }
}

void PlayerKill()
{
    printf("DEAD! \n");
    PlaySound(s_Death);
    
    playerAlive = false;
    
    currentPower = noPower;
    lastPower = noPower;
    
    neutralActive = true;
    blueActive=false;
    yellowActive=false;
    cyanActive= false;

    cyanKey = false;
    purpleKey = false;
    yellowKey = false;
    transitionTimer = transitionTime;
    

    for (actorIter currentActor = particles.begin();
         currentActor!= particles.end();
         currentActor++)
    {
        SetParticleType((*currentActor), PARTICLE_TYPE_INVISIBLE);
    }
    
    lastParticleAvailable = 0;

    for (actorIter currentActor = particles.begin() + lastParticleAvailable;
         currentActor!= particles.begin() + lastParticleAvailable + numberOfExplosionParticles;
         currentActor++)
    {
        SetParticleType((*currentActor), PARTICLE_TYPE_EXPLOSION);
    }
    
    
    EjectParticles(playerActor->GetDimensions().x + 64 + cameraX, playerActor->GetDimensions().y + 64 + cameraY, numberOfExplosionParticles);
    
}


void PlayerWin()
{
    printf("WIN! \n");
    playerWinning = true;
    
    currentPower = noPower;
    lastPower = noPower;
    
    neutralActive = true;
    blueActive=false;
    yellowActive=false;
    cyanActive= false;
    
    
    cyanKey = false;
    purpleKey = false;
    yellowKey = false;
    
    
    CURRENT_LEVEL++;
    if (CURRENT_LEVEL> LAST_LEVEL)
    {
        CURRENT_LEVEL = 0;
    }
    
    transitionTimer = transitionTime;
    
    for (actorIter currentActor = particles.begin();
         currentActor!= particles.end();
         currentActor++)
    {
        SetParticleType((*currentActor), PARTICLE_TYPE_WARP);
    }
 
    
    lastParticleAvailable = 0;
//    for (actorIter currentActor = particles.begin() + lastParticleAvailable;
//         currentActor!= particles.begin() + lastParticleAvailable + numberOfWarpParticles;
//         currentActor++)
//    {
//        SetParticleType((*currentActor), PARTICLE_TYPE_WARP);
//    }
    
    EjectParticles(playerActor->GetDimensions().x + 64 + cameraX, playerActor->GetDimensions().y + 64 + cameraY, numberOfWarpParticles);
}

void RotatePortal()
{
    portalAngle++;
    portalSprite->SetAngle(portalAngle);
}

//Returns true if they are overlapping
bool DidCollide(RenderableSprite* spriteA, RenderableSprite* spriteB)
{
    
//    SDL_Rect dimA = spriteA->GetRenderDimensions();
//    SDL_Rect dimB = spriteB->GetRenderDimensions();
    
    dimensions_t  dimA = spriteA->GetDimensions();
    dimensions_t  dimB = spriteB->GetDimensions();
    
    dimA.x += cameraX;
    dimA.y += cameraY;
    
    //!!!:CHECK THIS
    SDL_Rect rectA = spriteA->GetDst();
    SDL_Rect rectB = spriteB->GetDst();
    
    //Testing a small amount of give in the collision detection
    int collisionPadding = spriteB->GetDst().w/4;
    
    dimB.x+= collisionPadding;
    dimB.y+= collisionPadding;
    
    rectB.w-=collisionPadding *2;
    rectB.h-=collisionPadding *2;
    
//    printf("DimA-------------------\n");
//    dimA.Print();
//
//    printf("DimB-------------------\n");
//    dimB.Print();

    
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = dimA.x;
    rightA = dimA.x + rectA.w;
    topA = dimA.y;
    bottomA = dimA.y + rectA.h;
    
    //Calculate the sides of rect B
    leftB = dimB.x;
    rightB = dimB.x + rectB.w;
    topB = dimB.y;
    bottomB = dimB.y + rectB.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    
    return true;
}





void LoadLevel(SDL_Renderer* sdlRenderer)
{
    char file[200];
    
    //Clean up level first
    if (mapSurface)
    {
        SDL_FreeSurface(mapSurface);
    }
    
    sprintf(file,"level%lu.png", CURRENT_LEVEL);
    //sprintf(file,"testlevel8xf.png");
    
    if (! (mapSurface = IMG_Load(file)))
    {
        printf("Error loading image %s \n" , IMG_GetError());
    }
    
    MAP_WIDTH = mapSurface->w;
    MAP_HEIGHT = mapSurface->h;
    
    if (mapSurface== NULL)
    {
        printf("FAIL level load \n");
        
    }
    

    //spawnPoint.x = 0;
    //spawnPoint.y = 0;
    
    
    PlacePortal();
    PlaceKeys();
    
    //Move to spawn point
    //playerActor->SetPosX(SCREEN_WIDTH/2);
    //playerActor->SetPosY(SCREEN_HEIGHT/2);
    //playerSpawned = false;
    
    LoadSpawnPoint();

    
    if (playMusic)
    {
        //play level music
    }
    
    GAME_STATE = LEVEL;
    
}


void LoadBanner(SDL_Renderer* sdlRenderer)
{
    char bannerfile[200];
    printf("loaded banner\n");
    //Clean up banner first
    renderer->RemoveRenderable(bannerSprite);
    
    delete bannerSprite;
    
    sprintf(bannerfile,"levelslide%lu.png", CURRENT_LEVEL);

    if (! (bannerSurface = IMG_Load(bannerfile)))
    {
        printf("Error loading image %s \n" , IMG_GetError());
    }
    
    SDL_Rect* position = new SDL_Rect;
    position->x = 1;
    position->y = 1;
    position->w = SCREEN_WIDTH;
    position->h = SCREEN_HEIGHT;
    
    bannerSprite = new RenderableSprite();
    bannerSprite->SetSrc(NULL);
    bannerSprite->SetDst(position);
    bannerSprite->SetFlip(SDL_FLIP_NONE);
    
    bannerSprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, bannerSurface));
    
    bannerActor->SetActorView(bannerSprite);
    renderer->AddRenderable(bannerSprite);
    bannerActor->GetActorView()->SetCameraFollow(false);
}


void CreateBanner(SDL_Renderer* sdlRenderer)
{
    SDL_Rect* position = new SDL_Rect;
    
    printf("created banner\n");

    
    bannerSurface=IMG_Load("levelslide0.png");
    if(!bannerSurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }
    
    bannerSprite = new RenderableSprite();
    
    Color color;
    
    color.red = 255;
    color.green = 0;
    color.blue = 0;
    
    //Convert surface to texture and save to sprite texture object
    bannerSprite->SetTexture(ConvertSurfaceToTexture(sdlRenderer, bannerSurface));
    
    bannerSprite->SetAngle(0);
    bannerSprite->SetScaleX(1);
    bannerSprite->SetScaleY(1);
    
    position->x = 1;
    position->y = 1;
    position->w = SCREEN_WIDTH;
    position->h = SCREEN_HEIGHT;
    
    bannerSprite->SetCenter(0,0);
    
    bannerSprite->SetColor(color);
    
    bannerSprite->SetSrc(NULL);
    bannerSprite->SetDst(position);
    bannerSprite->SetFlip(SDL_FLIP_NONE);
    
    
    bannerActor = new Actor();
    bannerActor->SetMotion(false);
    bannerSprite->SetAngle(0);
    
    position->x = 1;
    position->y = 1;
    
    bannerActor->SetPosX(0);
    bannerActor->SetPosY(0);
    
    bannerActor->SetActorView(bannerSprite);
    
    actors.push_back(bannerActor);
    renderer->AddRenderable(bannerSprite);
    
    bannerActor->GetActorView()->SetCameraFollow(false);
    
    
}



void CleanLevel()
{
    for (actorIter i = pellets.begin();
         i !=pellets.end();
         i++)
    {
        DeletePellet((*i));
    }
    
    for (actorIter i = particles.begin();
         i != particles.end();
         i++)
    {
        
        (*i)->SetPosX(2000);
        (*i)->SetPosY(2000);
    }
    

    playerMoveUp->Stop();
    playerMoveUp->SetDisplacement(stopAction);
    
    
    
    GAME_STATE = LOADLEVEL;
    
}


void LoadFinalBanner()
{
    
}




void CheckForStartGame()
{
    if (buttonUp.pressed && !buttonUp.held)
    {
        GAME_STATE = LOADLEVEL;
    }
}


void HideSprites()
{
    for (actorIter i = actors.begin();
         i != actors.end();
         i++)
    {
        (*i)->SetPosX(-3000);
        (*i)->SetPosY(3000);
    }
    
    for (actorIter i = particles.begin();
         i != particles.end();
         i++)
    {
        PlaceParticleAt((*i), -2000, 2000);
    }
    
    for (actorIter i = scrollActors.begin();
         i != scrollActors.end();
         i++)
    {
        (*i)->SetPosX(-3000);
        (*i)->SetPosY(3000);
    }
    
    
    playerActor->SetPosX(-3000);
    playerActor->SetPosY(3000);
    
    portalActor->SetPosX(-3000);
    portalActor->SetPosY(3000);
    
    cyanKeyActor->SetPosX(-3000);
    cyanKeyActor->SetPosY(3000);
    
    purpleKeyActor->SetPosX(-3000);
    purpleKeyActor->SetPosY(3000);

    yellowKeyActor->SetPosX(-3000);
    yellowKeyActor->SetPosY(3000);

}


void PlacePortal()
{
    
    for (int x = 0 ; x < mapSurface->w ; x++)
    {
        for (int y = 0; y < mapSurface->h; y++)
        {
            checkPixel = GetPixel(mapSurface,x,y);
            mapColor = GetPixelColor(*checkPixel, mapSurface);
            
            if (SameColor(mapColor,endColor))
            {
                portalActor->SetPosX(x - 140);
                portalActor->SetPosY(y - 140);
            }
        }
    }
}




void PlaceKeys()
{
    for (int x = 0 ; x < mapSurface->w ; x++)
    {
        for (int y = 0; y < mapSurface->h; y++)
        {
            checkPixel = GetPixel(mapSurface,x,y);
            mapColor = GetPixelColor(*checkPixel, mapSurface);
            
            if (SameColor(mapColor,yellowKeyColor))
            {
                yellowKeyActor->SetPosY(y - 50);
                yellowKeyActor->SetPosX(x - 50);
            }
            
            if (SameColor(mapColor,cyanKeyColor))
            {
                cyanKeyActor->SetPosY(y - 50);
                cyanKeyActor->SetPosX(x - 50);
            }
            
            if (SameColor(mapColor,purpleKeyColor))
            {
                purpleKeyActor->SetPosY(y - 50);
                purpleKeyActor->SetPosX(x - 50);
            }
            
        }
    }
}




















