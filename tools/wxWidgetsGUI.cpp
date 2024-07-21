// wxWidgets "Run Program" Program
// For compilers that support precompilation, includes "wx/wx.h".
//g++ GUI.cpp -I/usr/local/Cellar/wxmac/3.0.4_2/lib/wx/include/osx_cocoa-unicode-3.0 -I/usr/local/Cellar/wxmac/3.0.4_2/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__ -L/usr/local/Cellar/wxmac/3.0.4_2/lib   -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL -lwx_osx_cocoau_xrc-3.0 -lwx_osx_cocoau_webview-3.0 -lwx_osx_cocoau_html-3.0 -lwx_osx_cocoau_qa-3.0 -lwx_osx_cocoau_adv-3.0 -lwx_osx_cocoau_core-3.0 -lwx_baseu_xml-3.0 -lwx_baseu_net-3.0 -lwx_baseu-3.0
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <stdlib.h>
/*
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
*/
//const int ID_PATCH = 101;
//const int ID_STOP = 102;

enum 
{
    ID_Run = 1,
    ID_PATCH,
    ID_STOP,
    ID_NEXT,
    ID_PREVIOUS,
};

 class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class FlexGridSizer : public wxFrame
{
public:
  FlexGridSizer(const wxString& title);
};

class SubPanel : public wxPanel
{
public:
    SubPanel(wxPanel *parent);

    void OnPatch(wxCommandEvent & event);
    void OnStop(wxCommandEvent & event);
    void OnNext(wxCommandEvent & event);
    void OnPrev(wxCommandEvent & event);

    wxButton *patch;
    wxButton *stop;
    wxButton *Next;
    wxButton *Previous;
    wxPanel *panel;
private:
    int count;
};

class wxImagePanel : public wxPanel
{
    wxBitmap resized;
    int w, h;
public:
    wxString Picture;
    wxImage image;
    wxPanel *panel;
    wxImagePanel(wxPanel* parent, wxString file, wxBitmapType format);
 
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void OnNext(wxCommandEvent & event);
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);
    DECLARE_EVENT_TABLE()
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
    wxBoxSizer *hbox;
    void OnNext(wxCommandEvent & event);
    SubPanel *LeftSubPanel;
    wxPanel *panel;
    wxFlexGridSizer *fgs;
    wxImagePanel * drawPane;
    wxImagePanel * InitPane;
    wxTextCtrl *tc_R;
    wxTextCtrl *tc_L; 
    wxTextCtrl *tc_ec; 
    wxTextCtrl *tc_rs; 
    wxTextCtrl *tc_MagR;
    wxTextCtrl *tc_Mag; 
    wxTextCtrl *tc_erf; 
    wxTextCtrl *tc_bl; 
    wxTextCtrl *tc_bn;


private:
    ~MyFrame();
    void OnRun(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}



BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
// catch paint events
EVT_PAINT(wxImagePanel::paintEvent)
//Size event
EVT_SIZE(wxImagePanel::OnSize)
END_EVENT_TABLE()
 
SubPanel::SubPanel(wxPanel * parent)
       : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN)
{
    count=0;
    panel = parent;
    patch = new wxButton(this, ID_PATCH, wxT("Patch"), 
	    wxPoint(10, 10));
    stop = new wxButton(this, ID_STOP, wxT("Stop"), 
	    wxPoint(10, 60));
    Connect(ID_PATCH, wxEVT_COMMAND_BUTTON_CLICKED, 
	    wxCommandEventHandler(SubPanel::OnPatch));
    Connect(ID_STOP, wxEVT_COMMAND_BUTTON_CLICKED, 
	    wxCommandEventHandler(SubPanel::OnStop));

    Next = new wxButton(this, ID_NEXT, wxT("Next"), 
	    wxPoint(10, 110));
    Previous = new wxButton(this, ID_PREVIOUS, wxT("Previous"), 
	    wxPoint(10, 160));
    Connect(ID_NEXT, wxEVT_COMMAND_BUTTON_CLICKED, 
	    wxCommandEventHandler(SubPanel::OnNext));
    Connect(ID_PREVIOUS, wxEVT_COMMAND_BUTTON_CLICKED, 
	    wxCommandEventHandler(SubPanel::OnPrev));
}

wxImagePanel::wxImagePanel(wxPanel* parent, wxString file, wxBitmapType format)
: wxPanel(parent, -1, wxPoint(-1, -1), wxSize(400, 500), wxBORDER_SUNKEN)
{
    Picture=file;
    panel = parent;
    //MyFrame *frame=(MyFrame *)this->GetParent();
    // load the file... ideally add a check to see if loading was successful
    if(wxFileExists(Picture)){
	image.LoadFile(Picture, format);
    }else{
	image.Create(400,500);
	//image.Destroy();
    }
    //image.LoadFile(file, format);
    //image.LoadFile(wxT("data_rho2.png"), format);
    //w = -1;
    //h = -1;
}
 


MyFrame::~MyFrame(){
    system("pkill code");
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Jellium_rod_gs",wxDefaultPosition,wxSize(900,500))
{

    wxInitAllImageHandlers();
    //flexgridsizer
    panel = new wxPanel(this, -1);
    hbox = new wxBoxSizer(wxHORIZONTAL);

    LeftSubPanel = new SubPanel(panel);
    hbox->Add(LeftSubPanel, 1, wxEXPAND | wxALL, 5);

    fgs = new wxFlexGridSizer(13, 2, 9, 5);
    wxStaticText *R = new wxStaticText(panel, -1, wxT("R"));
    wxStaticText *L = new wxStaticText(panel, -1, wxT("L"));
    wxStaticText *Ec = new wxStaticText(panel, -1, wxT("Ec"));
    wxStaticText *rs = new wxStaticText(panel, -1, wxT("rs"));
    wxStaticText *BoxMag_R = new wxStaticText(panel, -1, wxT("BoxMag_R"));
    wxStaticText *BoxMag = new wxStaticText(panel, -1, wxT("BoxMag"));
    wxStaticText *erf_eigen = new wxStaticText(panel, -1, wxT("erf_eigen"));
    wxStaticText *b_l = new wxStaticText(panel, -1, wxT("Coulomb_b_l"));
    wxStaticText *b_n = new wxStaticText(panel, -1, wxT("Coulomb_b_n"));
    tc_R = new wxTextCtrl(panel, -1);
    tc_L = new wxTextCtrl(panel, -1);
    tc_ec = new wxTextCtrl(panel, -1);
    tc_rs = new wxTextCtrl(panel, -1);
    tc_MagR = new wxTextCtrl(panel, -1);
    tc_Mag = new wxTextCtrl(panel, -1);
    tc_erf = new wxTextCtrl(panel, -1);
    tc_bl = new wxTextCtrl(panel, -1);
    tc_bn = new wxTextCtrl(panel, -1);
    //button
    wxButton * button = new wxButton(panel,wxID_EXIT, _T("Exit"));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, 
	    wxCommandEventHandler(MyFrame::OnExit));
    wxButton * Run = new wxButton(panel,ID_Run, _T("Run"));
    Connect(ID_Run, wxEVT_COMMAND_BUTTON_CLICKED, 
	    wxCommandEventHandler(MyFrame::OnRun));
    fgs->Add(R);
    fgs->Add(tc_R, 1, wxEXPAND);
    fgs->Add(L);
    fgs->Add(tc_L, 1, wxEXPAND);
    fgs->Add(Ec, 1, wxEXPAND);
    fgs->Add(tc_ec, 1, wxEXPAND);
    fgs->Add(rs);
    fgs->Add(tc_rs, 1, wxEXPAND);
    fgs->Add(BoxMag_R);
    fgs->Add(tc_MagR, 1, wxEXPAND);
    fgs->Add(BoxMag);
    fgs->Add(tc_Mag, 1, wxEXPAND);
    fgs->Add(erf_eigen);
    fgs->Add(tc_erf, 1, wxEXPAND);
    fgs->Add(b_l);
    fgs->Add(tc_bl, 1, wxEXPAND);
    fgs->Add(b_n);
    fgs->Add(tc_bn, 1, wxEXPAND);
    fgs->Add(button, 1, wxEXPAND);
    fgs->Add(Run, 1, wxEXPAND);
    //  fgs->AddGrowableRow(2, 1);
    //  fgs->AddGrowableCol(1, 1);
    hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);

	InitPane = new wxImagePanel(panel , wxT(""), wxBITMAP_TYPE_PNG);
	hbox->Add(InitPane, 1, wxEXPAND| wxEXPAND,5);
    panel->SetSizer(hbox);

    //menu
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Run, "&Run...\tCtrl-R",
	    "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MyFrame::OnRun, this, ID_Run);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Centre();
}

void SubPanel::OnNext(wxCommandEvent & WXUNUSED(event))
{   
//wxMessageBox("This is a wxWidgets OnNext",
//                "About jellium_rod_gs", wxOK | wxICON_INFORMATION);
MyFrame *frame=(MyFrame *)panel->GetParent();
//frame->drawPane->Destroy();
    count=count+1;
    char name[30];    
    sprintf(name,"./data_V%d.png",count);
    if(wxFileExists(wxString::FromUTF8(name))){
	//if(frame->drawPane->image.IsOk()){
	//    frame->drawPane->image.Destroy();
	//}
	frame->drawPane= new wxImagePanel(frame->InitPane, wxString::FromUTF8(name), wxBITMAP_TYPE_PNG);
    }else{count=count-1;}
}

void SubPanel::OnPrev(wxCommandEvent & WXUNUSED(event))
{
    count=count-1;
    MyFrame *frame=(MyFrame *)panel->GetParent();
    char name[30];    
    sprintf(name,"./data_V%d.png",count);
    if(wxFileExists(wxString::FromUTF8(name))){
	if(frame->drawPane->image.IsOk()){
	    frame->InitPane->image.Destroy();
	    frame->drawPane->image.Destroy();
	}
	frame->drawPane= new wxImagePanel(frame->InitPane, wxString::FromUTF8(name), wxBITMAP_TYPE_PNG);
    }else{count=count+1;}
}

void SubPanel::OnPatch(wxCommandEvent & WXUNUSED(event))
{
wxString str = wxGetTextFromUser(wxT("Enter the file name to patch:"));
MyFrame *frame=(MyFrame *)panel->GetParent();

wxString str_R = frame->tc_R->GetValue();
wxString str_L = frame->tc_L->GetValue();
wxString str_ec = frame->tc_ec->GetValue();
wxString str_rs = frame->tc_rs->GetValue();
wxString str_BoxMag_R = frame->tc_MagR->GetValue();
wxString str_BoxMag = frame->tc_Mag->GetValue();
wxString str_erf = frame->tc_erf->GetValue();
wxString str_bl = frame->tc_bl->GetValue();
wxString str_bn = frame->tc_bn->GetValue();

if(!str==false){
FILE *fp;
fp=fopen(str.mb_str().data(),"w");
const char* s =str_R.mb_str().data();//"Hello World !";
fprintf(fp,"R=%s #\n",s);
s =str_L.mb_str().data();
fprintf(fp,"L=%s #\n",s);
s =str_ec.mb_str().data();
fprintf(fp,"Ec=%s #\n",s);
s =str_rs.mb_str().data();
fprintf(fp,"rs=%s #\n",s);
s =str_BoxMag_R.mb_str().data();
fprintf(fp,"BoxMag_R=%s #\n",s);
s =str_BoxMag.mb_str().data();
fprintf(fp,"BoxMag=%s #\n",s);
s =str_erf.mb_str().data();
fprintf(fp,"erf_eigen=%s #\n",s); 
s =str_bl.mb_str().data();
fprintf(fp,"coulomb_expand_b_l=%s #\n",s); 
s =str_bn.mb_str().data();
fprintf(fp,"coulomb_expand_b_n=%s #\n",s); 
fclose(fp);
}
}


void MyFrame::OnExit(wxCommandEvent& event)
{
    system("pkill code");
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets GUI for jellium_rod_gs",
                 "About jellium_rod_gs", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnRun(wxCommandEvent& event)
{
//    wxLogMessage("Calculate jellium rod ground state");
    system("mpirun -np 25 ./code &");
/*
    FILE * fp;
    char buffer[80];
    fp=popen("pwd","r");
    fgets(buffer,sizeof(buffer),fp);
    printf("%s\n",buffer);
    pclose(fp);
*/
}


void SubPanel::OnStop(wxCommandEvent & WXUNUSED(event))
{
    system("pkill code");
  //count--;

  //Communicate *comm = (Communicate *) panel->GetParent();
  //comm->m_rp->m_text->SetLabel(wxString::Format(wxT("%d"), count));
}



/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
 
void wxImagePanel::paintEvent(wxPaintEvent & evt)
{
    // depending on your system you may need to look at double-buffered dcs
    //if(image.Ok()){
    wxPaintDC dc(this);
    render(dc);
   // }
}
 
/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void wxImagePanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    //if(image.Ok()){
    wxClientDC dc(this);
    render(dc);
   // }
}
 
/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void wxImagePanel::render(wxDC&  dc)
{
    //if(image.Ok()){
    int neww, newh;
    dc.GetSize( &neww, &newh );
 
    if( neww != w || newh != h )
    {
        resized = wxBitmap( image.Scale( neww, newh /*, wxIMAGE_QUALITY_HIGH*/ ) );
        w = neww;
        h = newh;
        dc.DrawBitmap( resized, 0, 0, false );
    }else{
        dc.DrawBitmap( resized, 0, 0, false );
    }
    //}
}
 
/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void wxImagePanel::OnSize(wxSizeEvent& event){
    //if(image.Ok()){
    Refresh();
    //skip the event.
    event.Skip();
//}
}
 

