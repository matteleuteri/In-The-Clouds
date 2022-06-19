#include "headers/Winmain.h"

static inline int64_t GetTicks()
{
    LARGE_INTEGER ticks;
    if (!QueryPerformanceCounter(&ticks))
    {
        // log error
    }
    return ticks.QuadPart;
}

static HRESULT LoadBitmapFromFile(IWICImagingFactory *pIWICFactory, LPCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap)
{
    IWICBitmapDecoder *pDecoder = NULL;
    IWICBitmapFrameDecode *pSource = NULL;
    // IWICStream *pStream = NULL;
    IWICFormatConverter *pConverter = NULL;
    // IWICBitmapScaler *pScaler = NULL;

    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(uri, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);

    if(SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pSource);
    }
    if(SUCCEEDED(hr))
    {
        hr = pIWICFactory->CreateFormatConverter(&pConverter);
    }
    if(SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
    }
    if(SUCCEEDED(hr))
    {
        hr = renderTarget->CreateBitmapFromWicBitmap(pConverter, ppBitmap);
    }
    return hr;
}

static void loadBitmapFile(IWICImagingFactory* pIWICFactory, std::filesystem::path bitmapFileName, ID2D1Bitmap **tBitmap)
{
    p /= bitmapFileName;
    LoadBitmapFromFile(pIWICFactory, p.c_str(), 20, 20, tBitmap);  
    p.remove_filename();
}

static void createResources(HWND hwnd, RECT* rc)
{
    ID2D1Factory* pD2DFactory = NULL;

    // both lines below return HRESULT, I should make sure they succeez
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    D2D1_SIZE_U clientSize = D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top);
    pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, clientSize), &renderTarget);
  
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red),   &brushes[0]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &brushes[1]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink),  &brushes[2]); 

    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory_));

    hr = pDWriteFactory_->CreateTextFormat(L"Gabriola", NULL, DWRITE_FONT_WEIGHT_REGULAR, 
                DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20.0f, L"en-us", &pTextFormat_);

    if (SUCCEEDED(hr))
    {
        hr = pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    }

    if (SUCCEEDED(hr))
    {
        hr = pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    // load images here
    IWICImagingFactory *pIWICFactory = NULL; 
    
    CoInitializeEx(NULL, COINIT_MULTITHREADED); 
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory));    

    p /= "assets";
    loadBitmapFile(pIWICFactory, "player_idle_01.png", &playerBitmap_idle_01);
    loadBitmapFile(pIWICFactory, "player_idle_02.png", &playerBitmap_idle_02);
    loadBitmapFile(pIWICFactory, "player_idle_03.png", &playerBitmap_idle_03);

    loadBitmapFile(pIWICFactory, "CloudLayer1_1.png", &BLayer1_1);

    loadBitmapFile(pIWICFactory, "WorldChunk_1.png", &chunk_bm_1);
    loadBitmapFile(pIWICFactory, "WorldChunk_2.png", &chunk_bm_2);
}

/*  THESE KEY FUNCTIONS BELOW ARE NOT FINAL  */
static void handleKeyDown(WPARAM wParam)
{
    if(wParam == VK_RIGHT) scene->player->goingRight = true;
    if(wParam == VK_LEFT)  scene->player->goingLeft = true;    

    if(wParam == VK_UP) up_Button->execute(scene); // up

    if(wParam == VK_DOWN) scene->player->flipBitmap();


    // if(wParam == 77) m_Button->execute(scene); // M
    // if(wParam == 80) p_Button->execute(scene); // P
    // if(wParam == 69) e_Button->execute(scene); // E
    // if(wParam == 81) q_Button->execute(scene); // Q
    // if(wParam == 82) r_Button->execute(scene); // R
    // if(wParam == 87) w_Button->execute(scene); // W
}

static void handleKeyUp(WPARAM wParam)
{
    if(wParam == VK_RIGHT) scene->player->goingRight = false;
    if(wParam == VK_LEFT)  scene->player->goingLeft = false;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    // POINT pt;
    switch (uMsg)
    {
        case WM_CLOSE: 
        {
            isRunning = false;
            // if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK) 
            DestroyWindow(hwnd);
            break;
        } 
        case WM_DESTROY:
        {
            isRunning = false;
            PostQuitMessage(0);
            break;
        } 
        // case WM_PAINT:
        // {
        // }
        case WM_LBUTTONDOWN:
        {
            // if(!scene->player->isActive) break;
            // Projectile proj(lParam, scene->player->x,  scene->player->y, projectile1Bitmap); // dont forget to free
            // scene->projectiles.push_back(proj);
        }
        case WM_KEYDOWN:
        {
            handleKeyDown(wParam);
            return 0;
        } 
        case WM_KEYUP:
        {
            handleKeyUp(wParam);
            return 0;
        } 
        default: 
        {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        } 
    }
    return result;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[]  = L"In The Clouds";
    
    WNDCLASS wc = { };
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = CLASS_NAME;

    if(RegisterClass(&wc))
    {
        HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"In The Clouds", 
                    WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 
                    CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);
        if(hwnd) 
        {
            isRunning = true;
            RECT rc;
            GetClientRect(hwnd, &rc);

            // this is a cpp17 feature, try to get rid of it
            p = std::filesystem::current_path().remove_filename();
            // wchar_t fnameBuffer[MAX_PATH];
            // GetModuleFileName(NULL, fnameBuffer, MAX_PATH);

            createResources(hwnd, &rc);

            std::vector<ID2D1Bitmap*> playerBitmaps = { playerBitmap_idle_01, playerBitmap_idle_02, playerBitmap_idle_03 };
            std::vector<ID2D1Bitmap*> chunkBitmaps = { chunk_bm_1, chunk_bm_1 };
            std::vector<ID2D1Bitmap*> backgroundBitmaps = { BLayer1_1 };

            std::vector<std::vector<ID2D1Bitmap*>> bitmaps = { playerBitmaps, chunkBitmaps, backgroundBitmaps };
            scene = std::make_unique<Scene>(GetTicks(), true, bitmaps);

            up_Button = new JumpButton();

            int64_t startTime = GetTicks();
            int64_t endTime;
            
            while(isRunning)
            {
                MSG msg;
                while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                {
                    if(msg.message == WM_QUIT)
                    {
                        isRunning = false;
                        break;
                    }
                    TranslateMessage(&msg);
                    DispatchMessageA(&msg);
                }

                endTime = GetTicks();

                scene->updateState(hwnd, endTime, startTime);
                scene->renderState(&rc, hwnd, renderTarget, brushes, pTextFormat_);
                    
                startTime = endTime;
            }
            // game is no longer running here
        }
    }
    return 0;
}
