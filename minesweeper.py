import numpy as np
import random

def initialize_board(size, num_mines):
    mine_map = np.zeros((size, size), dtype=int)
    game_board = np.zeros((size, size), dtype=int)  # 0: 未開示, 1: 開示, 2: フラグ
    
    # 地雷を配置
    mine_positions = random.sample([(x, y) for x in range(size) for y in range(size)], num_mines)
    for x, y in mine_positions:
        mine_map[x][y] = -1
    
    # 隣接地雷数のカウント
    for x in range(size):
        for y in range(size):
            if mine_map[x][y] == -1:
                continue
            mine_map[x][y] = sum(
                1 for dx, dy in [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]
                if 0 <= x+dx < size and 0 <= y+dy < size and mine_map[x+dx][y+dy] == -1
            )
    
    return mine_map, game_board

def print_board(size, game_board, mine_map):
    print("[y]")
    for y in reversed(range(size)):
        row = [" x" if game_board[x][y] == 0 else " o" if game_board[x][y] == 2 else f" {mine_map[x][y]}" for x in range(size)]
        print(f"{y} |" + " ".join(row))
    print("   " + "---" * size)
    print("   " + " ".join(f"{i:2}" for i in range(size)) + "  [x]")

def open_cell(x, y, size, mine_map, game_board):
    if mine_map[x][y] == -1:
        print("ゲームオーバー！")
        return False
    
    stack = [(x, y)]
    while stack:
        cx, cy = stack.pop()
        if game_board[cx][cy] == 1:
            continue
        game_board[cx][cy] = 1
        if mine_map[cx][cy] == 0:
            for dx, dy in [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]:
                nx, ny = cx + dx, cy + dy
                if 0 <= nx < size and 0 <= ny < size and game_board[nx][ny] == 0:
                    stack.append((nx, ny))
    return True

def play_minesweeper(size=8, num_mines=10):
    mine_map, game_board = initialize_board(size, num_mines)
    
    while True:
        print_board(size, game_board, mine_map)
        mode = input("モード選択 (1: セルを開く, 2: フラグ設置/解除): ")
        if mode not in {"1", "2"}:
            print("1または2を入力してください。")
            continue
        
        try:
            x, y = map(int, input("セルの座標を x y の形式で入力: ").split())
            if not (0 <= x < size and 0 <= y < size):
                raise ValueError
        except ValueError:
            print("正しい座標を入力してください。")
            continue
        
        if mode == "1":
            if not open_cell(x, y, size, mine_map, game_board):
                break
        else:
            game_board[x][y] = 2 if game_board[x][y] != 2 else 0
        
        # 勝利判定
        if sum(1 for i in range(size) for j in range(size) if game_board[i][j] == 0) == num_mines:
            print("Congraturation!")
            break

if __name__ == "__main__":
    play_minesweeper()
