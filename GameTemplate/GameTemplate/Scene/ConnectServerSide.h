#pragma once

#include "Scene/IScene.h"
#include <Windows.h>

namespace Network {
class GameServerThread;
} //Network 

namespace Graphics {
class TextureString;
} //Graphics 

namespace Scene {

/**
* @class ConnectServerSide
* @brief サーバー側のクライアント接続シーン
*/
class ConnectServerSide :public IScene {
public:
    /**
    * @brief コンストラクタ
    */
    ConnectServerSide();
    /**
    * @brief デストラクタ
    */
    ~ConnectServerSide();
    /**
    * @brief 更新
    * @param delta 前フレームからの差分時間
    */
    virtual void update(float delta) override;
    /**
    * @brief シーンが終了しているか
    */
    virtual bool isEndScene() const override;
    /**
    * @brief 描画
    */
    virtual void draw() override;
    /**
    * @brief 終了時処理
    * @return 次のシーン
    */
    virtual std::unique_ptr<IScene> end() override;
private:
    /**
    * @brief 接続ボタンが押されたときのイベント
    * @param port ポート番号
    */
    void puchConnectButton(int port);
private:
    bool mIsSceneEnd; //!< シーンが終了しているか
    bool mIsSelectConnect; //!< 接続を選択したか
    HWND mDlg; //!< ダイアログハンドル
    std::unique_ptr<Graphics::TextureString> mStr; //!< 表示するUI文字列
    std::unique_ptr<Network::GameServerThread> mServerThread; //!< サーバースレッド
};

} //Scene 