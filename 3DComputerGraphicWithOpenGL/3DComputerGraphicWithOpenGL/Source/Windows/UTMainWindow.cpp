// Copyright 2025. Team Unique Turtle ; https:github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "UTMainWindow.h"
#include "3DComputerGraphicWithOpenGL.h"
#include "Manager/ResourceManager.h"
#include "Manager/WindowManager.h"

UTMainWindow::UTMainWindow(const std::string& Title, int Width, int Height)
	: UTWindow(Title, Width, Height)
{
	Initialize();

	SelectedPart = 0;
	SelectedChapter = 0;
	SelectedSection = 0;
	SelectedCode = 0;
}

UTMainWindow::~UTMainWindow()
{

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
	ImGui::Begin(WStringToUtf8(L"입력").c_str(), &ShowInputWindow, CoreWindowFlags);
	InputWindow = ImGui::GetCurrentWindow();
	DrawInputWindow();
	ImGui::End();
	
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkPos.x, MainViewport->Size.y / 2.f + InputWindowTitleBarSize), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->Size.y / 2.f - InputWindowTitleBarSize), ImGuiCond_Always);
	ImGui::Begin(WStringToUtf8(L"설명").c_str(), &ShowDescriptionWindow, CoreWindowFlags);
	DescriptionWindow = ImGui::GetCurrentWindow();
	DrawDescriptionWindow();
	ImGui::End();
	
	ImGui::SetNextWindowPos(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->WorkPos.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(4.f * MainViewport->Size.x / 10.f, MainViewport->Size.y), ImGuiCond_Always);
	ImGui::Begin(WStringToUtf8(L"선택").c_str(), &ShowSelectorWindow, CoreWindowFlags);
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

	// remain this for R&D
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);
}

void UTMainWindow::RenderDrawData()
{
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(GetGLFWWindow());
}

void UTMainWindow::Initialize()
{
	UTWindow::Initialize();
	GuiContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(GuiContext);
	ImGui::StyleColorsDark();
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
	if (DebugContext.empty() == false)
	{
		ImGui::PushFont(BigFont);
		ImGui::SeparatorText(WStringToUtf8(L"디버그 정보").c_str());
		ImGui::PushTextWrapPos();
		ImGui::Text("%s", WStringToUtf8(DebugContext).c_str());
		ImGui::PopTextWrapPos();
		ImGui::PopFont();
	}

	ImGui::PushTextWrapPos();
	ImGui::Text("%s", WStringToUtf8(DescriptionContext).c_str());
	ImGui::PopTextWrapPos();
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

	ImGui::OpenPopup(WStringToUtf8(L"Introduction").c_str(), PopupFlags);
	if (ImGui::BeginPopupModal(WStringToUtf8(L"Introduction").c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::SeparatorText(WStringToUtf8(L"OpenGL로 배우는 3D 컴퓨터 그래픽 - biomatic").c_str());
		ImGui::Text(WStringToUtf8(L"이 프로젝트는 OpenGL API를 학습하고 실습하기 위해 시작되었습니다.").c_str());
		ImGui::Text(WStringToUtf8(L"내용은 \"3D Computer Graphics with OpenGL\"이라는 책을 기반으로 구성되어 있습니다.").c_str());
		ImGui::Text(WStringToUtf8(L"이 프로그램을 통해 각 파트와 챕터의 코드 예제를 직접 확인하고 실행할 수 있습니다.").c_str());
		ImGui::Text(WStringToUtf8(L"먼저 \"선택 창\"에서 파트, 챕터, 제목을 선택하세요.").c_str());
		ImGui::Text(WStringToUtf8(L"그 후 \"메인 창\"'에 코드가 표시되고, \"서브 창\"에서 실행 결과가 출력됩니다.").c_str());
		ImGui::NewLine();
		ImGui::Text(WStringToUtf8(L"책에 대해 더 알고 싶다면 아래 링크를 참고하세요.").c_str());
		ImGui::TextLinkOpenURL(WStringToUtf8(L"https://www.hanbit.co.kr/store/books/look.php?p_code=B1779572378").c_str());
		ImGui::NewLine();
		ImGui::Text(WStringToUtf8(L"이 프로그램의 오픈소스는 아래 링크에서 확인할 수 있습니다.").c_str());
		ImGui::TextLinkOpenURL(WStringToUtf8(L"https://github.com/biomaticals/3DComputerGraphicWithOpenGL").c_str());
		ImGui::NewLine();
		ImGui::SeparatorText(WStringToUtf8(L"biomatic 소개").c_str());
		ImGui::Text(WStringToUtf8(L"저는 대한민국에서 4년 경력의 게임 클라이언트 프로그래머입니다.").c_str());
		ImGui::NewLine();

		ImGui::Text(WStringToUtf8(L"기술 블로그는 아래 링크에서 확인하실 수 있습니다.").c_str());
		ImGui::TextLinkOpenURL(WStringToUtf8(L"https://biomaticals.notion.site/biomaticals").c_str());
		ImGui::NewLine();
		ImGui::Text(WStringToUtf8(L"아쉽게도 블로그는 현재 영어를 지원하지 않습니다.").c_str());
		ImGui::Text(WStringToUtf8(L"하지만 아래 전화번호나 이메일로 연락 주시면 영어로도 도움을 드릴 수 있습니다.").c_str());
		ImGui::NewLine();
		ImGui::NewLine();
		ImGui::Text(WStringToUtf8(L"문의는 아래 연락처를 이용해주세요.").c_str());
		ImGui::Text(WStringToUtf8(L"전화번호 : +82 10 3902 8624 (대한민국)").c_str());
		ImGui::Text(WStringToUtf8(L"이메일 : biomaticals@naver.com").c_str());
		ImGui::NewLine();

		if (ImGui::Button(WStringToUtf8(L"닫기").c_str(), ImVec2(-FLT_MIN, 0.f)))
		{
			ImGui::CloseCurrentPopup();
			*bOpen = false;
		}

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