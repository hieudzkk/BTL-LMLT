// KHAI BAO THU VIEN
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//KHAI BAO BIEN TINH TOAN CUC

//KHAI BÁO BIẾN TẠO CỬA SỔ WINDOW
static SDL_Window* g_window  = NULL ;

//KHAI BAO BIẾN ĐỂ RENDER HINH ANH
static SDL_Renderer* g_screen = NULL ;

//KHAI BÁO BIẾN ĐỂ XỬ LÝ SỰ KIỆN
static SDL_Event g_event ;

//KHAI BAO BIEN THONG SO CO DINH
const int SCREEN_HEIGHT = 600 ;
const int SCREEN_WIDTH = 1200;
const int SCREEN_BPP = 32 ;

//KHAI BAO BIEN COLOR_KEY
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175 ;
const int COLOR_KEY_B = 180 ;
const int RENDER_DRAW_COLOR = 255 ;

//XAY DUNG DOI TUONG , KHAI BÁO CÁC PHƯƠNG THỨC CỦA LỚP OBJECT
class Object
{
public :
    //HAM CONSTRUCTOR
    Object() ;
    //
    ~Object() ;

    // XAY DUNG PHUONG THUC

    //PHUONG THUC SET KICH THUOC
    void SetRect(const int& x , const int& y){rect_.x = x, rect_.y = y ;} ;

    //LAY KICH THUOC IMAGE
    SDL_Rect GetRect() const{return rect_ ;}
    //LAY IMAGE
    SDL_Texture* GetObject() const{return p_object_ ;} ;

    //PHUONG THUC LOAD IMAGE
    bool Load_Img(std::string path, SDL_Renderer* screen) ;

    //PHUONG THUC RENDERER
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL) ;

    //PHUONG THUC FREE()
    void Free() ;

protected :
    //BIEN LUU TRU HINH ANH
    SDL_Texture* p_object_ ;

    //BIEN LUU TRU KICH THUOC TAM ANH
    SDL_Rect rect_ ;
};

//....XÂY DỰNG CÁC PHƯƠNG THỨC CỦA LỚP OBJECT

//ĐỊNH NGHĨA PHƯƠNG THỨC CONTRUCTOR
Object::Object()
{
    p_object_ = NULL ;
    rect_.x = 0 ;
    rect_.y = 0 ;
    rect_.w = 0 ;
    rect_.w = 0 ;
    rect_.h = 0 ;
}

//PHƯƠNG THỨC DESTRUCTOR
Object::~Object()
{
    Free() ;
}

// PHUONG THUC Load_Img(STRING,RENDERER)
bool Object::Load_Img(std::string path , SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL ;

    //DOC TAM ANH THANH SURFACE
    SDL_Surface* load_surface = IMG_Load(path.c_str()) ;
    if(load_surface != NULL)
    {
        //TRANPARENCE BACKGROUND
        SDL_SetColorKey(load_surface, SDL_TRUE,SDL_MapRGB(load_surface->format ,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B)) ;

        //CHUYEN SURFACE THANH TEXTURE LUU DU TAT CA THONG TIN VE TAM ANH
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface) ;
        if(new_texture != NULL)
        {
            rect_.w = load_surface->w ;
            rect_.h = load_surface->h ;

        }

        //FREE(XOA) SURFACE
        SDL_FreeSurface(load_surface) ;
    }
    p_object_ = new_texture  ;
    return p_object_!=NULL ;
}

//PHUONG THUC RENDER
void Object::Render(SDL_Renderer* des ,const SDL_Rect* clip )
{
    //TAO DOI TUONG RENDERQUAD CO KICH THUOC
    SDL_Rect renderquad = {rect_.x,rect_.y,rect_.w,rect_.h} ;
    SDL_RenderCopy(des,p_object_,clip,&renderquad) ;
}

//PHUONG THUC FREE DE GIAI PHONG BO NHO
void Object::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_) ;
        p_object_ = NULL ;
        rect_.w = 0 ;
        rect_.h = 0 ;
    }
}

// TAO DOI TUONG g_background THUOC LOP Object

////Main

Object g_background ;
// HAM KHOI TAO Init()
bool Init()
{
    bool result = true ;
    //khoi tao
    int result_init = SDL_Init(SDL_INIT_VIDEO) ;

    //NẾU KHỞI TẠO SDL KHÔNG THÀNH CÔNG
    if(result_init < 0 )
        result = false ;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ;
    // TẠO CỬA SỔ WINDOW
    g_window = SDL_CreateWindow("GAMESDL 2.0",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN) ;
    // NẾU TẠO CỬA SỔ WINDOW THẤT BẠI
    if(g_window == NULL)
    {
        result = false ;
    }
    //NEU THANH CONG
    else
    {
        // TAO RENDERER CHO WINDOW
        g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED) ;
        //NEU RENDER LOI
        if(g_screen == NULL)
            result = false ;
        //TAO RENDER THANH CONG
        else
        {
            // KHOI TAO RENDERER COLOR
            SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR) ;

            //KHOI TAO PNG LOADING, TAO CO
            int imgFlags = IMG_INIT_PNG ;
            if(!(IMG_Init(imgFlags) && imgFlags))
            {
                result = false ;

            }

        }
    }
    return result ;
}
// HAM LOAD ANH
bool LoadBackground()
{
    // PATH ANH : image//
    bool result_LoadBackground = g_background.Load_Img("image//Samurai//Attack_1.png",g_screen)  ;
    //LOAD ANH BI LOI
    if(result_LoadBackground == false)
    {
        return false ;
    }
    return true ;


}

//HAM CLOSE
void close()
{
    //GIAI PHONG BO NHO CHUA BACKGROUND
    g_background.Free() ;

    //GIAI PHONG BO NHO CHUA RENDER
    SDL_DestroyRenderer(g_screen) ;
    g_screen = NULL ;

    //GIAI PHONG BO NHO CHUA DOI TUONG WINDOW
    SDL_DestroyWindow(g_window) ;

    //KET THUC CHUONG TRINH
    IMG_Quit() ;
    SDL_QUIT ;

}

// HAM MAIN
int main(int argc,char* argv[])
{
    //KHOI TAO SDL KHONG THANH CONG
    if(Init() == false)
        return "LỖI KHỞI TẠO SDL" ;

    //LOAD ANH BI LOI
    if(LoadBackground() == false)
        return "KHÔNG LOAD BACKGROUND";

    //MAP CUA GAME
    //LOAD IMAGE


    //TAO VONG LAP CHAY VO HAN DE CHUONG TRINH LOAD TAM ANH
    bool is_quit = false ;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event)!=0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true ;
            }
        }

        //SET LAI MAU CHO TAM HINH
        SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);

        //REFRESH LAI MAN HINH
        SDL_RenderClear(g_screen) ;

        g_background.Render(g_screen,NULL) ;

        //UPDATE LAI MAN HINH
        SDL_RenderPresent(g_screen) ;
    }
    close() ;
    return 0 ;
}
