#include "headers/Winmain.h"

static HRESULT LoadBitmapFromResource(IWICImagingFactory *pIWICFactory, LPCWSTR resourceName, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap)
{
    if(pIWICFactory == NULL || ppBitmap == NULL || renderTarget == NULL)
    {
        return E_POINTER;
    }

    // Find and load the embedded resource into memory
    HINSTANCE hInst = GetModuleHandle(NULL);
    HRSRC hRes = FindResource(hInst, resourceName, RT_RCDATA);
    if(hRes == NULL)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    DWORD resSize = SizeofResource(hInst, hRes);
    HGLOBAL hResData = LoadResource(hInst, hRes);
    if(hResData == NULL)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    LPVOID resPtr = LockResource(hResData);
    if(resPtr == NULL)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    IWICStream *pStream = NULL;
    IWICBitmapDecoder *pDecoder = NULL;
    IWICBitmapFrameDecode *pSource = NULL;
    IWICFormatConverter *pConverter = NULL;

    HRESULT hr = pIWICFactory->CreateStream(&pStream);
    if(SUCCEEDED(hr))
    {
        hr = pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(resPtr), resSize);
    }
    if(SUCCEEDED(hr))
    {
        hr = pIWICFactory->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnLoad, &pDecoder);
    }
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

    if(pConverter) pConverter->Release();
    if(pSource) pSource->Release();
    if(pDecoder) pDecoder->Release();
    if(pStream) pStream->Release();

    return hr;
}

static IWICImagingFactory* createResources(HWND hwnd, RECT* rc)
{
    ID2D1Factory* pD2DFactory = NULL;

    // both lines below return HRESULT, I should make sure they succeed
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    D2D1_SIZE_U clientSize = D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top);
    pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, clientSize), &renderTarget);
  
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

    IWICImagingFactory *pIWICFactory = NULL; 
    CoInitializeEx(NULL, COINIT_MULTITHREADED); 
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory));    
    
    return pIWICFactory;
}

static std::vector<ID2D1Bitmap*> loadBitmapVector(IWICImagingFactory* pIWICFactory, std::vector<std::wstring>& assetNames)
{
    std::vector<ID2D1Bitmap*> bitmapVector = {};
    for(auto& asset : assetNames)
    {
        ID2D1Bitmap *currBitmap = NULL;
        HRESULT hr = LoadBitmapFromResource(pIWICFactory, asset.c_str(), 20, 20, &currBitmap);
        if(FAILED(hr) || currBitmap == NULL)
        {
            char message[512];
            snprintf(message, sizeof(message), "Failed to load asset '%ls' (hr=0x%08lX)\n", asset.c_str(), (unsigned long)hr);
            OutputDebugStringA(message);
            continue;
        }
        bitmapVector.push_back(currBitmap);
    }
    return bitmapVector;
}

static void handleKeyDown(WPARAM wParam)
{
    if(wParam == VK_RIGHT) scene->player->xSpeed = 0.5f;
    if(wParam == VK_LEFT) scene->player->xSpeed = -0.5f;

    if(wParam == VK_UP) up_Button->execute(scene);  

    if(wParam == VK_DOWN && scene->player != NULL && !scene->player->isInAir)
    {
        scene->player->fallOff();
    }
    // if(wParam == 77) scene->player->onPlatform = true; // M
    // if(wParam == 80) 
    // {
    //     scene->x += 5;
    // } // P
}

static void handleKeyUp(WPARAM wParam)
{
    if(wParam == VK_RIGHT) scene->player->xSpeed = 0.0f;
    if(wParam == VK_LEFT) scene->player->xSpeed = 0.0f;
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
            break;
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

            IWICImagingFactory* pIWICFactory = createResources(hwnd, &rc);

            // JsonParser *jp = new JsonParser("ResourceTree.json");
            // jp->parse();

            std::vector<std::wstring> playerIdleAssetNames = { L"PLAYER2_IDLE_01", L"PLAYER2_IDLE_02", L"PLAYER2_IDLE_03" };
            std::vector<ID2D1Bitmap*> playerIdleBitmaps = loadBitmapVector(pIWICFactory, playerIdleAssetNames);
            Animation* playerIdleAnm = new Animation(playerIdleBitmaps, 0, GetTickCount(), 100);
            std::vector<std::wstring> playerJumpAssetNames = { L"PLAYER2_JUMP_01", L"PLAYER2_JUMP_02", L"PLAYER2_JUMP_03", L"PLAYER2_JUMP_04"};
            std::vector<ID2D1Bitmap*> playerJumpBitmaps = loadBitmapVector(pIWICFactory, playerJumpAssetNames);
            Animation* playerJumpAnm = new Animation(playerJumpBitmaps, 0, GetTickCount(), 100);
            std::map<int, Animation*> playerAnimations;
            playerAnimations[0] = playerIdleAnm;
            playerAnimations[1] = playerJumpAnm;
            AnimationController *playerAnimationController = new AnimationController(playerAnimations);

            std::vector<std::wstring> chunk1AssetNames = { L"WORLDCHUNK_1_1", L"WORLDCHUNK_1_2" };
            std::vector<ID2D1Bitmap*> chunk1Bitmaps = loadBitmapVector(pIWICFactory, chunk1AssetNames);
            Animation* chunk1Anm = new Animation(chunk1Bitmaps, 0, GetTickCount(), 100);
            std::map<int, Animation*> chunk1Animations;
            chunk1Animations[0] = chunk1Anm;
            AnimationController *chunk1AnimationController = new AnimationController(chunk1Animations);

            std::vector<std::wstring> chunk2AssetNames = { L"WORLDCHUNK_2_1", L"WORLDCHUNK_2_2" };
            std::vector<ID2D1Bitmap*> chunk2Bitmaps = loadBitmapVector(pIWICFactory, chunk2AssetNames);
            Animation* chunk2Anm = new Animation(chunk2Bitmaps, 0, GetTickCount(), 100);
            std::map<int, Animation*> chunk2Animations;
            chunk2Animations[0] = chunk2Anm;
            AnimationController *chunk2AnimationController = new AnimationController(chunk2Animations);

            std::vector<std::wstring> chunk3AssetNames = { L"WORLDCHUNK_1_1", L"WORLDCHUNK_1_2" };
            std::vector<ID2D1Bitmap*> chunk3Bitmaps = loadBitmapVector(pIWICFactory, chunk3AssetNames);
            Animation* chunk3Anm = new Animation(chunk3Bitmaps, 0, GetTickCount(), 100);
            std::map<int, Animation*> chunk3Animations;
            chunk3Animations[0] = chunk3Anm;
            AnimationController *chunk3AnimationController = new AnimationController(chunk3Animations);

            std::vector<std::wstring> backgroundAssetNames = { L"BACKGROUND" };
            std::vector<ID2D1Bitmap*> backgroundBitmaps = loadBitmapVector(pIWICFactory, backgroundAssetNames);
            Animation* backgroundAnm = new Animation(backgroundBitmaps, 0, GetTickCount(), 100);
            std::map<int, Animation*> backgroundAnimations;
            backgroundAnimations[0] = backgroundAnm;
            AnimationController *backgroundAnimationController = new AnimationController(backgroundAnimations);

            std::vector<std::wstring> cloudLayer1AssetNames = { L"CLOUDLAYER_1_2", L"CLOUDLAYER_1_1", L"CLOUDLAYER_1_3", L"CLOUDLAYER_1_1" };
            std::vector<ID2D1Bitmap*> cloudLayer1Bitmaps = loadBitmapVector(pIWICFactory, cloudLayer1AssetNames);
            Animation* cloudLayer1Anm = new Animation(cloudLayer1Bitmaps, 0, GetTickCount(), 100);
            std::map<int, Animation*> cloudLayer1Animations;
            cloudLayer1Animations[0] = cloudLayer1Anm;
            AnimationController *cloudLayer1AnimationController = new AnimationController(cloudLayer1Animations);

            std::vector<std::wstring> cloudLayer2AssetNames = { L"CLOUDLAYER_2_2", L"CLOUDLAYER_2_1", L"CLOUDLAYER_2_3", L"CLOUDLAYER_2_1" };
            std::vector<ID2D1Bitmap*> cloudLayer2Bitmaps = loadBitmapVector(pIWICFactory, cloudLayer2AssetNames);
            Animation* cloudLayer2Anm = new Animation(cloudLayer2Bitmaps, 0, GetTickCount(), 100);
            std::map<int, Animation*> cloudLayer2Animations;
            cloudLayer2Animations[0] = cloudLayer2Anm;
            AnimationController *cloudLayer2AnimationController = new AnimationController(cloudLayer2Animations);

            std::vector<AnimationController*> animationControllers = { playerAnimationController, chunk1AnimationController, chunk2AnimationController, 
                        chunk3AnimationController, backgroundAnimationController, cloudLayer1AnimationController, cloudLayer2AnimationController };

            scene = std::make_unique<Scene>(GetTickCount(), true, animationControllers, 0.0f, 0.0f, &rc);
            
            // here is where I can mess with screen resolution stuff
            // scene->width = (float)rc.right - rc.left;

            up_Button = new JumpButton();
            
            int32_t startTime = GetTickCount();
            int32_t endTime;
            const int32_t targetFrameMs = 16; // cap at ~60 FPS to stop busy spin
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
                endTime = GetTickCount();
                int32_t frameTime = endTime - startTime;
                if (frameTime < targetFrameMs)
                {
                    Sleep(targetFrameMs - frameTime);
                    endTime = GetTickCount();
                }
                scene->updateState(hwnd, endTime, startTime);
                scene->renderState(hwnd, renderTarget, pTextFormat_);                    
                startTime = endTime;
            }
        }
    }
    return 0;
}
