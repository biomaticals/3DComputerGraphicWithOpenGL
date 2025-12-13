// Copyright 2025. Team Unique Turtle ; https:github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "UTMainWindow.h"
#include "3DComputerGraphicWithOpenGL.h"
#include "Manager/ResourceManager.h"
#include "Manager/WindowManager.h"
#include "InsideStaticMath.h"

using namespace InsideStaticMath;

UTMainWindow::UTMainWindow(const std::string& Title, int Width, int Height)
	: UTWindow(Title, Width, Height)
{
	Initialize();

	SelectedPart = 0;
	SelectedChapter = 0;
	SelectedSection = 0;
	SelectedCode = 0;

	InputContext = L"\"선택 창\"에서 파트, 챕터, 코드를 선택해주세요.";
	DescriptionContext = L"\"선택 창\"에서 파트, 챕터, 코드를 선택해주세요.";
}

UTMainWindow::~UTMainWindow()
{

}

void UTMainWindow::Initialize()
{
	UTWindow::Initialize();
	GuiContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(GuiContext);
	ImGui::StyleColorsDark();
}

void UTMainWindow::NewFrame()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	ImGui::SetCurrentContext(GuiContext);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UTMainWindow::RenderUI()
{
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = true;
	static bool no_move = true;
	static bool no_resize = true;
	static bool no_collapse = true;
	static bool no_close = true;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool unsaved_document = false;
	
	ImGuiWindowFlags CoreWindowFlags = 0;
	if (no_titlebar)        CoreWindowFlags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       CoreWindowFlags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           CoreWindowFlags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            CoreWindowFlags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          CoreWindowFlags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        CoreWindowFlags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             CoreWindowFlags |= ImGuiWindowFlags_NoNav;
	if (no_background)      CoreWindowFlags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  CoreWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   CoreWindowFlags |= ImGuiWindowFlags_UnsavedDocument;
	
	//1. Windows
	const ImGuiViewport* MainViewport = ImGui::GetMainViewport();
	float InputWindowTitleBarSize = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2;
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkPos.x, MainViewport->WorkPos.y),ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->Size.y / 2.f), ImGuiCond_Always);
	ImGui::PushFont(MediumFont);
	ImGui::Begin(WStringToUtf8(L"입력").c_str(), &ShowInputWindow, CoreWindowFlags);
	ImGui::PopFont();
	InputWindow = ImGui::GetCurrentWindow();
	DrawInputWindow();
	ImGui::End();
	
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkPos.x, MainViewport->Size.y / 2.f + InputWindowTitleBarSize), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->Size.y / 2.f - InputWindowTitleBarSize), ImGuiCond_Always);
	ImGui::PushFont(MediumFont);
	ImGui::Begin(WStringToUtf8(L"설명").c_str(), &ShowDescriptionWindow, CoreWindowFlags);
	ImGui::PopFont();
	DescriptionWindow = ImGui::GetCurrentWindow();
	DrawDescriptionWindow();
	ImGui::End();
	
	ImGui::SetNextWindowPos(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->WorkPos.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(4.f * MainViewport->Size.x / 10.f, MainViewport->Size.y), ImGuiCond_Always);
	ImGui::PushFont(MediumFont);
	ImGui::Begin(WStringToUtf8(L"선택").c_str(), &ShowSelectorWindow, CoreWindowFlags);
	ImGui::PopFont();
	SelectorWindow = ImGui::GetCurrentWindow();
	DrawSelectorWindow();
	ImGui::End();
	
	//2. Main Menu
	if (bShowIntroduction)
	{
		ShowIntroductionWindow(&bShowIntroduction);
	}

	if (ImGui::BeginMainMenuBar())
	{
		ImGui::MenuItem(WStringToUtf8(L"소개").c_str(), nullptr, &bShowIntroduction);
		ImGui::EndMainMenuBar();
	}

	//remain this for R&D
	//if (show_demo_window)
	// 	ImGui::ShowDemoWindow(&show_demo_window);
}

void UTMainWindow::RenderDrawData()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(GetGLFWWindow());
}

ImGuiContext* UTMainWindow::GetGuiContext() const
{
	return GuiContext;
}

void UTMainWindow::DrawInputWindow()
{
	ImGui::PushTextWrapPos();
	ImGui::Text("%s", WStringToUtf8(InputContext).c_str());
	ImGui::PopTextWrapPos();
}

void UTMainWindow::DrawSelectorWindow()
{
	if (Book.Parts.size() == 0)
	{
		if (RESOURCE_MANAGER->LoadTitleContext())
		{
			Book = RESOURCE_MANAGER->GetBook();
		}
		else
		{
			ImGui::Text("Failed to load title context.");
			return;
		}
	}

	for (unsigned int i = 0 ; i < Book.Parts.size(); i++)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Appearing);
		if (Book.Parts[i].IsValid() && ImGui::CollapsingHeader(WStringToUtf8(Book.Parts[i].Title).c_str()))
		{
			ImGui::Indent();
			for (unsigned int j = 0 ; j < Book.Parts[i].Chapters.size() ; j++)
			{
				if (Book.Parts[i].Chapters[j].IsValid() && ImGui::CollapsingHeader(WStringToUtf8(Book.Parts[i].Chapters[j].Title).c_str()))
				{
					ImGui::Indent();
					for (unsigned int k = 0 ; k < Book.Parts[i].Chapters[j].Sections.size() ; k++)
					{
						if (Book.Parts[i].Chapters[j].Sections[k].IsValid() && ImGui::CollapsingHeader(WStringToUtf8(Book.Parts[i].Chapters[j].Sections[k].Title).c_str()))
						{
							ImGui::Indent();
							for (unsigned int l = 0 ; l <Book.Parts[i].Chapters[j].Sections[k].ExampleCodes.size() ; l++)
							{
								if (Book.Parts[i].Chapters[j].Sections[k].ExampleCodes[l].IsValid())
								{
									bool IsSelected = false;
									if (i == SelectedPart && j == SelectedChapter && k == SelectedSection && l == SelectedCode)
									{
										IsSelected = true;
										float Time = (float)ImGui::GetTime();
										float Blink = sin(2.f * Time) * 0.5f + 1.f;
										ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f * Blink, 0.2f, 0.2f, 1.0f));
									}

									if (ImGui::MenuItem(WStringToUtf8(Book.Parts[i].Chapters[j].Sections[k].ExampleCodes[l].Title).c_str(), nullptr, false, true))
									{
										RESOURCE_MANAGER->FindInputAndDescriptionContext(i, j, k, l, InputContext, DescriptionContext);
										OUTPUT_WINDOW->SetSelectedExampleCodeData(i, j, k, l);
										glfwShowWindow(OUTPUT_WINDOW->GetGLFWWindow());
										OnSelected(i, j, k, l);
									}

									if (IsSelected)
									{
										ImGui::PopStyleColor();
									}
								}
							}
							ImGui::Unindent();
						}
					}
					ImGui::Unindent();
				}
			}
			ImGui::Unindent();
		}
	}
}

void UTMainWindow::DrawDescriptionWindow()
{
	if (ExplanationContext.empty() == false)
	{
		ImGui::PushFont(BigFont);
		ImGui::SeparatorText(WStringToUtf8(L"예제 코드").c_str());
		ImGui::PopFont();
		ImGui::PushTextWrapPos();
		ImGui::Text("%s", WStringToUtf8(ExplanationContext).c_str());
		ImGui::PopTextWrapPos();
	}

	if (DebugContext.empty() == false)
	{
		ImGui::PushFont(BigFont);
		ImGui::SeparatorText(WStringToUtf8(L"디버그 정보").c_str());
		ImGui::PopFont();
		ImGui::PushFont(MediumFont);
		ImGui::PushTextWrapPos();
		ImGui::Text("%s", WStringToUtf8(DebugContext).c_str());
		ImGui::PopTextWrapPos();
		ImGui::PopFont();
	}

	if (DescriptionContext.empty() == false)
	{
		ImGui::PushFont(BigFont);
		ImGui::SeparatorText(WStringToUtf8(L"내용").c_str());
		ImGui::PopFont();
		ImGui::PushTextWrapPos();
		ImGui::Text("%s", WStringToUtf8(DescriptionContext).c_str());
		ImGui::PopTextWrapPos();
	}
}

void UTMainWindow::ShowIntroductionWindow(bool* bOpen)
{
	const ImGuiViewport* MainViewport = ImGui::GetMainViewport();

	ImGuiWindowFlags WindowFlags{};
	WindowFlags |= ImGuiWindowFlags_NoResize;
	WindowFlags |= ImGuiWindowFlags_UnsavedDocument;

	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkSize.x / 2.f - 400.f, MainViewport->WorkSize.y /2.f - 250.f), ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkSize.x / 2.f - 400.f, MainViewport->WorkSize.y /2.f - 250.f), ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkSize.x / 2.f - 400.f, MainViewport->WorkSize.y /2.f - 250.f), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(800, 500.f), ImGuiCond_Appearing);
	ImGui::SetNextWindowFocus();

	ImGuiPopupFlags PopupFlags{};
	PopupFlags |= ImGuiPopupFlags_NoOpenOverExistingPopup;
	PopupFlags |= ImGuiPopupFlags_AnyPopupId;
	PopupFlags |= ImGuiPopupFlags_AnyPopupLevel;
	PopupFlags |= ImGuiPopupFlags_MouseButtonLeft;

	ImGui::OpenPopup(WStringToUtf8(L"소개").c_str(), PopupFlags);
	if (ImGui::BeginPopupModal(WStringToUtf8(L"소개").c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		// 3D CG With OpenGL
		ImGui::PushFont(BigFont);
		ImGui::SeparatorText(WStringToUtf8(L"3D CG With OpenGL").c_str());
		ImGui::PopFont();
		ImGui::Text(WStringToUtf8(L"이 프로젝트는 OpenGL API를 체계적으로 학습하고 실습하기 위해 제작한 학습용 프로젝트입니다.").c_str());
		ImGui::Text(WStringToUtf8(L"주우석 저자의 [오픈지엘로 배우는 3차원 컴퓨터 그래픽스]를 기반으로 하되, 각 예제를 최신 라이브러리를 활용하여 재구성했습니다.\n\n").c_str());
		
		ImGui::Text(WStringToUtf8(L"이 학습 도구를 통해 이론, 코드, 실행 결과까지 확인할 수 있습니다.").c_str());
		ImGui::Text(WStringToUtf8(L"\"선택 창\"에서 파트, 챕터, 코드를 선택하면, \"입력 창\"에 입력 코드를 표시합니다.").c_str());
		ImGui::Text(WStringToUtf8(L"\"설명 창\"에서는 주요 함수들과 이론을 설명하고 디버그 정보를 보여주고, \"결과 창\"에서 결과를 확인합니다.").c_str());

		ImGui::NewLine();
		ImGui::Text(WStringToUtf8(L"책에 대해 더 알고 싶다면 아래 링크를 참고합니다.").c_str());
		ImGui::TextLinkOpenURL(WStringToUtf8(L"https://www.hanbit.co.kr/store/books/look.php?p_code=B1779572378").c_str());
		ImGui::NewLine();
		ImGui::Text(WStringToUtf8(L"이 프로그램의 오픈소스는 아래 링크에서 확인할 수 있습니다.").c_str());
		ImGui::TextLinkOpenURL(WStringToUtf8(L"https://github.com/biomaticals/3DComputerGraphicWithOpenGL").c_str());
		ImGui::NewLine();

		// biomatic
		ImGui::PushFont(BigFont);
		ImGui::SeparatorText(WStringToUtf8(L"biomaticals 소개").c_str());
		ImGui::PopFont();
		ImGui::Text(WStringToUtf8(L"책임지고 완성하는 게임 클라이언트 프로그래머 방정현입니다.").c_str());
		ImGui::Text(WStringToUtf8(L"EVRSTUDIO에서 [무당 : 두개의 심장] 개발 및 XBox Showcase 2025 참가했습니다.").c_str());
		ImGui::Text(WStringToUtf8(L"주로 카메라 및 전투.비전투 연출을 담당했고, 관련 에픽을 이끌었습니다.").c_str());
		ImGui::Text(WStringToUtf8(L"연출, 수학, 렌더링, 물리, 엔진, 음악, 요리등에 흥미를 갖고 있습니다.").c_str());
		ImGui::NewLine();
		ImGui::Text(WStringToUtf8(L"또한 기술 블로그를 운영하고 있으며 아래 링크에서 확인하실 수 있습니다.").c_str());
		ImGui::TextLinkOpenURL(WStringToUtf8(L"https://biomaticals.notion.site/biomaticals").c_str());
		ImGui::NewLine();
		ImGui::Text(WStringToUtf8(L"모든 관심과 문의는 언제든지 환영합니다.").c_str());
		ImGui::Text(WStringToUtf8(L"전화번호 : +82 10 3902 8624 (대한민국)").c_str());
		ImGui::Text(WStringToUtf8(L"이메일 : biomaticals@naver.com").c_str());
		ImGui::NewLine();
		ImGui::PushFont(MonospaceFont);
		ImGui::Text(WStringToUtf8(L"========================================================\n").c_str());
		ImGui::Text(WStringToUtf8(L".###..###..###..##.##...#...###.###..##....#...#....####\n").c_str());
		ImGui::Text(WStringToUtf8(L".# ##..#..##.##.##.##..#.#...#...#..#..#..#.#..#....#...\n").c_str());
		ImGui::Text(WStringToUtf8(L".####..#..##.##.#.#.#.#####..#...#..#....#####.#....####\n").c_str());
		ImGui::Text(WStringToUtf8(L".# ##..#..##.##.#...#.#...#..#...#..#..#.#...#.#.......#\n").c_str());
		ImGui::Text(WStringToUtf8(L".###..###..###..#...#.#...#..#..###..##..#...#.####.####\n").c_str());
		ImGui::Text(WStringToUtf8(L"========================================================\n").c_str());
		ImGui::PopFont();
		
		// 닫기
		ImGui::PushFont(MediumFont);
		if (ImGui::Button(WStringToUtf8(L"닫기").c_str(), ImVec2(-FLT_MIN, 0.f)))
		{
			ImGui::CloseCurrentPopup();
			*bOpen = false;
		}
		ImGui::PopFont();

		ImGui::EndPopup();
		return;
	}

	ImGui::EndPopup();
	ImGui::SetWindowFocus(WStringToUtf8(L"Introduction").c_str());
}

void UTMainWindow::OnSelected(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int Code)
{
	SelectedPart = Part;
	SelectedChapter = Chapter;
	SelectedSection = Section;
	SelectedCode = Code;
}