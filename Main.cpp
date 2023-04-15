# include <Siv3D.hpp> // OpenSiv3D v0.6.8

struct Ball
{
	Vec2 pos;
	int32 num;
	double size;
};

int32 divideprime(int32 n)
{
	for(int32 i=2;i<n;++i)
	{
		if(n%i==0)
		{
			return i;
		}
	}
	return 1;
}

void Main()
{
	Scene::SetBackground(ColorF{0.6, 0.8, 0.7});

	const Font font{FontMethod::MSDF, 48, Typeface::Bold};

	int32 seq = 0;
	double time = 0;
	int32 time_int = 0;

	Array<Ball> balls = {};
	bool isholding = false;
	Ball holding={};
	int32 score = 0;
	double speed = 2000;

	while (System::Update())
	{
		time += Scene::DeltaTime();
		if (seq == 0)
		{
			font(U"画面をクリックしてスタート").drawAt(32, Scene::Center(), Palette::White);
			if (time < 1)
			{
				Rect{Scene::Size()}.draw(ColorF(0, 0, 0, 1 - time));
				continue;
			}
			if (MouseL.down())
			{
				time = 0;
				time_int = 0;
				seq = 1;
				isholding = false;
				balls = {};
				score = 0;
				speed = 2000;
			}
			continue;
		}
		for (auto i = 0; i < balls.size(); ++i)
		{
			Circle{ balls[i].pos, balls[i].size }.draw(Palette::Black);
			Circle{ balls[i].pos, balls[i].size - 2 }.draw(Palette::White);
			font(U"{}"_fmt(balls[i].num)).drawAt(balls[i].size, balls[i].pos, ColorF{ 0.2, 0.4, 0.8 });
		}
		if (isholding) {
			Circle{ holding.pos, holding.size }.draw(Palette::Black);
			Circle{ holding.pos, holding.size - 2 }.draw(Palette::White);
			font(U"{}"_fmt(holding.num)).drawAt(holding.size, holding.pos, ColorF{ 0.2, 0.4, 0.8 });
		}
		font(U"{}"_fmt(balls.size())).drawAt(40, Vec2{ 30, 30 }, ColorF{ 0.2, 0.4, 0.8 });
		Rect{ 0, Scene::Height() * 7 / 8, Scene::Width(), Scene::Height() / 8 }.draw(Palette::White);
		Line{ Scene::Width() / 4, Scene::Height() * 7 / 8, Scene::Width() / 4, Scene::Height() }.draw(Palette::Black);
		Line{ Scene::Width() * 2 / 4, Scene::Height() * 7 / 8, Scene::Width() * 2 / 4, Scene::Height() }.draw(Palette::Black);
		Line{ Scene::Width() * 3 / 4, Scene::Height() * 7 / 8, Scene::Width() * 3 / 4, Scene::Height() }.draw(Palette::Black);
		font(U"{}"_fmt(2)).drawAt(40, Vec2{ Scene::Width() * 1 / 8, Scene::Height() * 15 / 16 }, ColorF{ 0.2, 0.4, 0.8 });
		font(U"{}"_fmt(3)).drawAt(40, Vec2{ Scene::Width() * 3 / 8, Scene::Height() * 15 / 16 }, ColorF{ 0.2, 0.4, 0.8 });
		font(U"{}"_fmt(5)).drawAt(40, Vec2{ Scene::Width() * 5 / 8, Scene::Height() * 15 / 16 }, ColorF{ 0.2, 0.4, 0.8 });
		font(U"{}"_fmt(7)).drawAt(40, Vec2{ Scene::Width() * 7 / 8, Scene::Height() * 15 / 16 }, ColorF{ 0.2, 0.4, 0.8 });

		font(U"Score {}"_fmt(score)).drawAt(40, Vec2{ Scene::Width() * 3 / 4,20 }, ColorF{ 0.2, 0.4, 0.8 });
		if (seq == 2)
		{
			if (time < 3)
			{
				continue;
			}
			font(U"クリックして続ける").drawAt(32, Scene::Center(), Palette::White);
			if (MouseL.down())
			{
				seq = 0;
				time = 0;
			}
			continue;
		}

		if(isholding)
		{
			if(MouseL.up())
			{
				balls << holding;
				isholding = false;
			}
		}
		else if(MouseL.down())
		{
			for (int32 i = balls.size() - 1; i >= 0; --i)
			{
				if(balls[i].pos.distanceFrom(Cursor::Pos())<balls[i].size)
				{
					int32 n = divideprime(balls[i].num);
					isholding = true;
					if (n == 1) {

						holding = balls[i];
						balls.remove_at(i);
					}else
					{
						holding = Ball{ Cursor::Pos(),n,balls[i].size * 0.8 };
						balls[i].num /= n;
						balls[i].size *= 0.9;
					}
					break;
				}
			}
		}




		if (time_int < Floor(time))
		{
			time_int = Floor(time);
			for (auto i = 0; i < 3; ++i)
			{
				if (Random(0.0, 1.0) > 0.8)
				{
					int32 n = Random(2, 10);
					double s = Random(40.0, 80.0);
					if(Random(0.0,1.0)<0.5)
					{
						n *= Random(2, 10);
						s *= 1.1;
					}
					if (Random(0.0, 1.0) < 0.03)
					{
						n *= Random(2, 10);
						s *= 1.1;
					}
					if (Random(0.0, 1.0) < 0.03)
					{
						n *= Random(2, 10);
						s *= 1.1;
					}
					if (Random(0.0, 1.0) < 0.03)
					{
						n *= Random(2, 10);
						s *= 1.1;
					}
					if (Random(0.0, 1.0) < 0.03)
					{
						n *= Random(2, 10);
						s *= 1.1;
					}

					balls << Ball{Vec2{Random(20, Scene::Width()-20), -100}, n, s};
				}
			}
		}

		for (auto i=0;i<balls.size(); ++i)
		{
			balls[i].pos.y += Scene::DeltaTime() * speed / balls[i].size;
			if(balls[i].pos.y>Scene::Height()*7/8)
			{
				int32 n = 2;
				if(balls[i].pos.x>Scene::Width() / 4)
				{
					n =3;
				}
				if (balls[i].pos.x > Scene::Width()*2 / 4)
				{
					n =5;
				}
				if (balls[i].pos.x > Scene::Width() *3/ 4)
				{
					n =7;
				}
				if(n==balls[i].num)
				{
					balls.remove_at(i--);
					score += n * 100;
					speed += 10;
				}else
				{
					seq = 2;
					time = 0;
				}
			}
		}
		if (isholding) {
			holding.pos = Cursor::Pos();
		}
		


	}
}
