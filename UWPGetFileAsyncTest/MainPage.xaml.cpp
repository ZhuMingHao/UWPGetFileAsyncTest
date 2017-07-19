//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace UWPGetFileAsyncTest;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Search;
using namespace Platform::Collections;
using namespace concurrency;
using namespace std;
using namespace Windows::Storage::Pickers;


// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409
MainPage::MainPage()
{

	InitializeComponent();

}


void UWPGetFileAsyncTest::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (Windows::Storage::AccessCache::StorageApplicationPermissions::FutureAccessList->ContainsItem("PickedFolderToken")) {

		create_task(Windows::Storage::AccessCache::StorageApplicationPermissions::FutureAccessList->GetFolderAsync("PickedFolderToken")).then([this](StorageFolder^ folder)
		{
			//do some stuff
			//QueryOptions Q();
			QueryOptions Q(CommonFolderQuery::GroupByMonth);
			auto query = folder->CreateFileQuery(CommonFileQuery::DefaultQuery);
			return query->GetFilesAsync();
		}).then([this](IVectorView<StorageFile^>^ f)
		{
			txt_currentPath->Text = "dddddd";

		}).then([this](task<void> t)
		{
			try
			{
				t.get();
			}
			catch (Platform::Exception^ e)
			{
				txt_currentPath->Text = "FOLDER NOT FOUND";
			}
		});
	}
}


void UWPGetFileAsyncTest::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FolderPicker^ folderPicker = ref new FolderPicker();
	folderPicker->SuggestedStartLocation = PickerLocationId::Desktop;
	folderPicker->FileTypeFilter->Append("*");

	create_task(folderPicker->PickSingleFolderAsync()).then([this](StorageFolder^ folder)
	{
		if (folder)
		{
			Windows::Storage::AccessCache::StorageApplicationPermissions::
				FutureAccessList->AddOrReplace("PickedFolderToken", folder);
		}
		else
		{

		}
	});
}
