# Facade

A facade is just a coordinator class that hide complexity. You're probably already building facades in every LLD interview without calling them that. Your `Game` class in Tic Tac Toe? That's a facade. Any orchestrator that coordinates multiple components behind a clean interface? Also a facade.

Almost nobody names this pattern when they're using it. The pattern name is more useful when you're wrapping existing messy code. Like, if you inherit a complex subsystem with awkward APis, you write a facade to make it easier to use. But in LLD interviews, you're designing clena orchestrators from scratch, which happens to be the same structure. You're likely already doing the right thing instinctively, you just don't need to announce it.

```java
enum GameState {
    IN_PROGRESS,
    WON,
    DRAW
}

class Board {
    public boolean placeMark(int row, int col, String mark) {
        // Mark logic
        return true;
    }

    public boolean checkWin(int row, int col) {
        // Win logic
        return false;
    }
}

class Player {
    private String mark;

    public Player(String mark) {
        this.mark = mark;
    }

    public String getMark() {
        return mark;
    }
}

class Game {
    private Board board;
    private Player playerX;
    private Player playerO;
    private Player currentPlayer;
    private GameState state;

    public Game() {
        this.board = new Board();
        this.playerX = new Player("X");
        this.playerO = new Player("O");
        this.currentPlayer = playerX;
        this.state = GameState.IN_PROGRESS;
    }
    
    public boolean makeMove(int row, int col) {
        if (state != GameState.IN_PROGRESS) return false;
        if (!board.placeMark(row, col, currentPlayer.getMark())) return false;

        if (board.checkWin(row, col)) {
            state = GameState.WON;
        } else if (board.isFull()) {
            state = GameState.DRAW;
        } else {
            currentPlayer = (currentPlayer == playerX) ? playerO : playerX;
        }
        return true;
    }
}

// Usage
// simple interface hides all the coordination
Game game = new Game();
game.makeMove(0, 0);
game.makeMove(1, 1);

The pattern name just describes what good orchestrator design looks like. Build it naturally, name it if it helps communicate, but don't worry if you never mention Facade by name in an interview.