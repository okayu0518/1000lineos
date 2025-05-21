# 1000行で作るOSをやる
- 西野先生がおすすめしていたヤツ
- https://operating-system-in-1000-lines.vercel.app/ja/04-boot

# CSR (control and status registers)
- CSRは、プロセッサの動作モードの制御、ステータス情報の保持、例外処理、割り込み制御、性能カウンタなど、多岐にわたる特権的な機能や情報にアクセスするためのレジスタ群です。
- アクセス: csrrw (CSR Read and Write), csrrs (CSR Read and Set), csrrc (CSR Read and Clear) などの専用命令を使ってアクセスします。

```
[okayu0518@x1:~/projects/1000lineos] (main)
% llvm-nm shell.bin.o | grep _binary_shell_bin_size
00010260 A _binary_shell_bin_size

[okayu0518@x1:~/projects/1000lineos] (main)
% ls -al shell.bin
-rwxrwxr-x 1 okayu0518 okayu0518 66144 May 21 20:58 shell.bin

[okayu0518@x1:~/projects/1000lineos] (main)
% python3 -c 'print(0x10260)'
66144
```
