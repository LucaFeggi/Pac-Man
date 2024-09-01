#include "Score.hpp"

Score::Score(SDL_Renderer* Renderer, TTF_Font* Font) :
	MyTextures { Renderer, Renderer, Renderer, Renderer },
	Font(Font),
	ActualScore(0),
	OldScore(0)
{
	InitHighScore();
	MyTextures[0].LoadFromRenderedText("0", Color::White, Font);
	MyTextures[1].LoadFromRenderedText("Score", Color::White, Font);
	MyTextures[3].LoadFromRenderedText("HighScore", Color::White, Font);
}

Score::~Score() {
	TermHighScore();
	Font = nullptr;
}

void Score::Update() {
	UpdateScoreTexture();
	UpdateHighScoreTexture();
}

void Score::Restart() {
	ActualScore = 0;
	UpdateScoreTexture();
	OldScore = 0;
}

void Score::Draw() {
	SDL_Rect MyRects[4] = {
		{ 0, int(StdBlockSize + StdBlockSize), MyTextures[0].GetWidth(), MyTextures[0].GetHeight()},
		{ 0, int(StdBlockSize - StdBlockSize / 2), MyTextures[1].GetWidth(), MyTextures[1].GetHeight() } ,
		{ WindowWidth / 2, int(StdBlockSize + StdBlockSize), MyTextures[2].GetWidth(), MyTextures[2].GetHeight() },
		{ WindowWidth / 2, int(StdBlockSize - StdBlockSize / 2), MyTextures[3].GetWidth(), MyTextures[3].GetHeight() },
	};
	for (int i = 0; i < 4; i++) {
		MyTextures[i].Render(nullptr, &MyRects[i]);
	}
}

void Score::Add(int x) {
	ActualScore += x;
}

unsigned int Score::Get() {
	return ActualScore;
}

void Score::InitHighScore() {
	std::stringstream String;
	std::ifstream HighScoreInput("Source/TextFiles/HighScore.txt");
	HighScoreInput >> HighScore;
	String << HighScore;
	MyTextures[2].LoadFromRenderedText(String.str(), Color::White, Font);
}

void Score::TermHighScore() {
	std::ofstream HighScoreOutput;
	HighScoreOutput.open("Source/TextFiles/HighScore.txt");
	HighScoreOutput << HighScore;
	HighScoreOutput.close();
}

void Score::UpdateScoreTexture() {
	std::stringstream String;
	if (OldScore != ActualScore) {
		OldScore = ActualScore;
		String << ActualScore;
		MyTextures[0].LoadFromRenderedText(String.str(), Color::White, Font);
	}
}

void Score::UpdateHighScoreTexture() {
	if (HighScore < ActualScore) {
		std::stringstream String;
		String << ActualScore;
		MyTextures[2].LoadFromRenderedText(String.str(), Color::White, Font);
		HighScore = ActualScore;
	}
}