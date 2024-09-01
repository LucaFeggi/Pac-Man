#include "Board.hpp"

Board::Board(SDL_Renderer* Renderer) :
	DefaultSketch(
		"  p                      b  "
		"                            "
		"                            "
		"                            "
		"############################"
		"#............##............#"
		"#.####.#####.##.#####.####.#"
		"#o####.#####.##.#####.####o#"
		"#.####.#####.##.#####.####.#"
		"#..........................#"
		"#.####.##.########.##.####.#"
		"#.####.##.########.##.####.#"
		"#......##....##....##......#"
		"######.##### ## #####.######"
		"     #.##### ## #####.#     "
		"     #.##    B     ##.#     "
		"     #.## ###==### ##.#     "
		"######.## #      # ##.######"
		"      .   #I P C #   .      "
		"######.## #      # ##.######"
		"     #.## ######## ##.#     "
		"     #.##    f     ##.#     "
		"     #.## ######## ##.#     "
		"######.## ######## ##.######"
		"#............##............#"
		"#.####.#####.##.#####.####.#"
		"#.####.#####.##.#####.####.#"
		"#o..##.......M .......##..o#"
		"###.##.##.########.##.##.###"
		"###.##.##.########.##.##.###"
		"#......##....##....##......#"
		"#.##########.##.##########.#"
		"#.##########.##.##########.#"
		"#..........................#"
		"############################"
		"c                          i"
		"                            "),
	ActualSketch(DefaultSketch),
	BoardTexture(Renderer)
{
	BoardTexture.LoadFromFile("Source/Textures/Board24.png");
	BoardTexture.SetColor(Color::Blue);	
}

Board::~Board() {

}

std::string Board::Get() {
	return ActualSketch;
}

void Board::StartAnimationTimer() {
	AnimationTimer.Start();
}

void Board::StopAnimationTimer() {
	AnimationTimer.Stop();
}

bool Board::IsAnimationCompleted() {
	if (AnimationTimer.GetTicks() > 2000) {
		return true;
	}
	return false;
}

void Board::Animation() {
	if (int(AnimationTimer.GetTicks() / 250) % 2 == 0) {
		BoardTexture.SetColor(Color::White);
		return;
	}
	BoardTexture.SetColor(Color::Blue);
}

void Board::ModPiece(int Index, char Substitute) {
	ActualSketch.at(Index) = Substitute;
}

char Board::GetPiece(int Index) {
	return ActualSketch.at(Index);
}

void Board::Draw() {
	BoardTexture.Render();
}

void Board::Reset() {
	ActualSketch = DefaultSketch;
	BoardTexture.SetColor(Color::Blue);
	AnimationTimer.Stop();
}

void Board::Restart() {
	Reset();
}