# 1000行で作るOSをやる
- 西野先生がおすすめしていたヤツ
- https://operating-system-in-1000-lines.vercel.app/ja/04-boot

# CSR (control and status registers)
- CSRは、プロセッサの動作モードの制御、ステータス情報の保持、例外処理、割り込み制御、性能カウンタなど、多岐にわたる特権的な機能や情報にアクセスするためのレジスタ群です。
- アクセス: csrrw (CSR Read and Write), csrrs (CSR Read and Set), csrrc (CSR Read and Clear) などの専用命令を使ってアクセスします。
