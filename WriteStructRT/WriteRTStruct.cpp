#define _UNICODE
#include "WriteRTStruct.h"
#include "iostream"
#include "conio.h"
#include "itkImage.h"
#include "gdcmImage.h"
#include "gdcmReader.h"
#include "gdcmFile.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmWriter.h"
#include "gdcmItem.h"
#include "gdcmTag.h"
#include "gdcmImageWriter.h"
#include "gdcmAttribute.h"
#include "gdcmImageReader.h"
#include "gdcmSmartPointer.h"
#include "dcmtk\dcmrt\drtplan.h"
#include "dcmtk\dcmdata\dcfilefo.h"
#include "dcmtk\dcmdata\dcdeftag.h"
#include "dcmtk\config\osconfig.h"
#include "dcmtk\dcmdata\dctk.h"
#include "dcmtk\dcmdata\dcmetinf.h"
#include "dcmtk\dcmdata\dcrlerp.h"
#include "dcmtk\dcmimgle\dcmimage.h"
#include "dcmtk\dcmdata\dcuid.h"
#include "dcmtk\dcmjpeg\djencode.h"
#include "dcmtk\dcmdata\dcvrda.h"
#include "dcmtk\dcmdata\dcvrtm.h"
//
#include "gdcmUIDGenerator.h"
#include "itkGDCMImageIO.h"

#include <time.h>
//
//
//
//
using namespace gdcm;

using namespace std;


WriteRTStruct::WriteRTStruct()
{
}


WriteRTStruct::~WriteRTStruct()
{
}

std::string WriteRTStruct::dicomDate(){

	time_t now = time(NULL);
	struct tm tstruct;
	char buf[40];
	tstruct = *localtime(&now);
	//format: day DD-MM-YYYY
	strftime(buf, sizeof(buf), "%A %d/%m/%Y", &tstruct);
	return buf;
}

std::string WriteRTStruct::dicomTime(){

	time_t now = time(NULL);
	struct tm tstruct;
	char buf[40];
	tstruct = *localtime(&now);
	//format: HH:mm:ss
	strftime(buf, sizeof(buf), "%X", &tstruct);
	return buf;
}



void WriteRTStruct::RTStruct(std::string contours, std::string SOPInstanceUID1, std::string SOPInstanceUID2, std::string SOPInstanceUID3, std::string SOPInstanceUID4, std::string SOPInstanceUID5, std::string SOPInstanceUID6, std::string Requiredetails)
{

	char uid[100];

	DcmFileFormat fileformat;
	DcmRepresentationParameter *params;
	DcmDataset *dataset = fileformat.getDataset();

	typedef itk::Point<double, 2> PointType;
	typedef itk::Image< unsigned short, 2>    ImageType;

	std::string StructuresetSop;
	std::string strlist;
	std::string framereferenceID;
	std::vector<string> SOPInstanceUIDList;
	std::vector<string> ContourList;

	std::vector<string> ReqDatas;

	std::stringstream check1(Requiredetails);

	std::string intermediate;

	while (getline(check1, intermediate, ','))
	{
		ReqDatas.push_back(intermediate);
	}


	std::string currentDate = dicomDate();
	std::string currentTime = dicomTime();


	std::string DicomPath = ReqDatas.at(0);
	std::string patientname = ReqDatas.at(1);
	std::string Patientid = ReqDatas.at(2);
	std::string gender = ReqDatas.at(3);
	std::string DOB = ReqDatas.at(4);
	std::string age = ReqDatas.at(5);
	std::string studyDes = ReqDatas.at(6);
	std::string seriesDes = ReqDatas.at(7);
	std::string Maufacture = ReqDatas.at(8);
	std::string Manufacturemodel = ReqDatas.at(9);
	std::string studyInstanceUID = ReqDatas.at(10);
	std::string SeriesInstanceUID = ReqDatas.at(11);
	std::string ReferenceframeInstance = ReqDatas.at(12);
	std::string versionno = ReqDatas.at(13);

	std::string t1 = "RS.";
	std::string t2 = ".dcm";

	string dicomfile2 = t1 + dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT) + t2;

	std::string dir = DicomPath;

	std::string fileName1 = dir + "//" + dicomfile2;

	std::cout<< "contour" << contours;

	std::vector<vector<double>>ContourFinalList;

	std::vector<double>cplist;

	std::stringstream check2(contours);

	std::string intermediate1;

	while (getline(check2, intermediate1, ','))
	{
		ContourList.push_back(intermediate1);
	}


	for each (std::string str12 in ContourList)
	{
		double d = std::stod(str12);
		cplist.push_back(d);
		std::cout << "doubleval" << d;
	}

	std::cout << "cplist" << cplist.size();

	std::vector<string>SOPInstanceUIDList1; //splitting

	std::stringstream check3(SOPInstanceUID1);

	std::string intermediate2;

	while (getline(check3, intermediate2, ','))
	{
		SOPInstanceUIDList1.push_back(intermediate2);
	}


	std::vector<string>SOPInstanceUIDList2; //splitting

	std::stringstream check4(SOPInstanceUID2);

	std::string intermediate3;

	while (getline(check4, intermediate3, ','))
	{
		SOPInstanceUIDList2.push_back(intermediate3);
	}


	std::vector<string>SOPInstanceUIDList3; //splitting

	std::stringstream check5(SOPInstanceUID3);

	std::string intermediate4;

	while (getline(check5, intermediate4, ','))
	{
		SOPInstanceUIDList3.push_back(intermediate4);
	}

	std::vector<string>SOPInstanceUIDList4; //splitting

	std::stringstream check6(SOPInstanceUID4);

	std::string intermediate5;

	while (getline(check6, intermediate5, ','))
	{
		SOPInstanceUIDList4.push_back(intermediate5);
	}

	std::vector<string>SOPInstanceUIDList5; //splitting

	std::stringstream check7(SOPInstanceUID5);

	std::string intermediate6;

	while (getline(check7, intermediate6, ','))
	{
		SOPInstanceUIDList5.push_back(intermediate6);
	}
	std::vector<string>SOPInstanceUIDList6; //splitting

	std::stringstream check8(SOPInstanceUID6);

	std::string intermediate7;

	while (getline(check8, intermediate7, ','))
	{
		SOPInstanceUIDList6.push_back(intermediate7);
	}

	std::cout << "SOPInstance--1" << SOPInstanceUIDList1.size();
	std::cout << "SOPInstance--2" << SOPInstanceUIDList2.size();
	std::cout << "SOPInstance--3" << SOPInstanceUIDList3.size();
	std::cout << "SOPInstance--4" << SOPInstanceUIDList4.size();
	std::cout << "SOPInstance--5" << SOPInstanceUIDList5.size();
	std::cout << "SOPInstance--6" << SOPInstanceUIDList6.size();

	ContourFinalList.push_back(cplist);

	for (int i = 0; i < SOPInstanceUIDList1.size(); i++)
	{
		SOPInstanceUIDList.push_back(SOPInstanceUIDList1[i]);
	}

	for (int i = 0; i < SOPInstanceUIDList2.size(); i++)
	{
		SOPInstanceUIDList.push_back(SOPInstanceUIDList2[i]);
	}

	for (int i = 0; i < SOPInstanceUIDList3.size(); i++)
	{
		SOPInstanceUIDList.push_back(SOPInstanceUIDList3[i]);
	}
	for (int i = 0; i < SOPInstanceUIDList4.size(); i++)
	{
		SOPInstanceUIDList.push_back(SOPInstanceUIDList4[i]);
	}

	for (int i = 0; i < SOPInstanceUIDList5.size(); i++)
	{
		SOPInstanceUIDList.push_back(SOPInstanceUIDList5[i]);
	}

	for (int i = 0; i < SOPInstanceUIDList6.size(); i++)
	{
		SOPInstanceUIDList.push_back(SOPInstanceUIDList6[i]);
	}

	std::string studyID = studyInstanceUID;
	std::string seriesID = SeriesInstanceUID;

	std::cout << "finalcontour" << ContourFinalList.size();

	dataset->putAndInsertString(DCM_SOPClassUID, UID_RTStructureSetStorage);
	StructuresetSop = dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT);
	dataset->putAndInsertString(DCM_SOPInstanceUID, StructuresetSop.c_str());

	dataset->putAndInsertString(DCM_StudyInstanceUID, studyID.c_str());
	dataset->putAndInsertString(DCM_SeriesInstanceUID, seriesID.c_str());
	dataset->putAndInsertString(DCM_Modality, "RTSTRUCT");

	dataset->putAndInsertString(DCM_StudyDescription, studyDes.c_str());

	dataset->putAndInsertString(DCM_PatientName, patientname.c_str());

	dataset->putAndInsertString(DCM_PatientID, Patientid.c_str());

	dataset->putAndInsertString(DCM_PatientSex, gender.c_str());

	dataset->putAndInsertString(DCM_PatientBirthDate, DOB.c_str());

	dataset->putAndInsertString(DCM_PatientAge, age.c_str());

	dataset->putAndInsertString(DCM_SpecificCharacterSet, "ISO_IR 100");
	dataset->putAndInsertString(DCM_SamplesPerPixel, "1");
	dataset->putAndInsertString(DCM_PhotometricInterpretation, "MONOCHROME2");
	dataset->putAndInsertString(DCM_Rows, "512");
	dataset->putAndInsertString(DCM_Columns, "512");
	dataset->putAndInsertString(DCM_BitsAllocated, "16");
	dataset->putAndInsertString(DCM_BitsStored, "16");
	dataset->putAndInsertString(DCM_HighBit, "15");
	dataset->putAndInsertString(DCM_PixelRepresentation, "0");
	dataset->putAndInsertString(DCM_SmallestImagePixelValue, "0");
	dataset->putAndInsertString(DCM_LargestImagePixelValue, "256");

	dataset->putAndInsertString(DCM_ManufacturerModelName, Manufacturemodel.c_str());
	dataset->putAndInsertString(DCM_Manufacturer, Maufacture.c_str());

	dataset->putAndInsertString(DCM_StudyDescription, studyDes.c_str());
	dataset->putAndInsertString(DCM_SoftwareVersions, versionno.c_str());
	dataset->putAndInsertString(DCM_InstanceCreationDate, currentDate.c_str());
	dataset->putAndInsertString(DCM_InstanceCreationTime, currentTime.c_str());
	dataset->putAndInsertString(DCM_SeriesDescription, seriesDes.c_str());

	dataset->putAndInsertString(DCM_StructureSetLabel, "123");
	dataset->putAndInsertString(DCM_StructureSetDate, currentDate.c_str());
	dataset->putAndInsertString(DCM_StructureSetTime, currentTime.c_str());

	DcmItem *RFR, *StusyIn, *SeriesIns, *Cts, *SSRS, *RROS, *BS = NULL;

	cout << "SOPINSTANCEUIDList" << SOPInstanceUIDList.size();

	if (dataset->findOrCreateSequenceItem(DCM_ReferencedFrameOfReferenceSequence, RFR).good())
	{
		framereferenceID = ReferenceframeInstance;
		RFR->putAndInsertString(DCM_FrameOfReferenceUID, framereferenceID.c_str());
		if (RFR->findOrCreateSequenceItem(DCM_RTReferencedStudySequence, StusyIn).good())
		{
			StusyIn->putAndInsertString(DCM_ReferencedSOPClassUID, "Study Component Management SOP Class");
			string SOPINS = studyInstanceUID;
			StusyIn->putAndInsertString(DCM_ReferencedSOPInstanceUID, SOPINS.c_str());

			if (StusyIn->findOrCreateSequenceItem(DCM_RTReferencedSeriesSequence, SeriesIns).good())
			{
				string SeriesINS = SeriesInstanceUID;
				SeriesIns->putAndInsertString(DCM_SeriesInstanceUID, SeriesINS.c_str());

				int p = -1;
				for (int R = 0; R<SOPInstanceUIDList.size(); R++)
				{

					p++;
					if (SeriesIns->findOrCreateSequenceItem(DCM_ContourImageSequence, Cts, p).good())
					{
						string CTINS = SOPInstanceUIDList[R];
						Cts->putAndInsertString(DCM_ReferencedSOPClassUID, UID_SecondaryCaptureImageStorage);
						Cts->putAndInsertString(DCM_ReferencedSOPInstanceUID, CTINS.c_str());
					}
				}
			}
		}
	}

	cout<< "List" << ContourFinalList.size();
	for (int i = 0; i<ContourFinalList.size(); i++){
		cout << "CPFinalList1" << i;
		///  qDebug()<<"SSequence"<<p<<i;
		if (dataset->findOrCreateSequenceItem(DCM_StructureSetROISequence, SSRS, i).good()){
			SSRS->putAndInsertString(DCM_ROINumber, std::to_string(i + 1).c_str());
			SSRS->putAndInsertString(DCM_ReferencedFrameOfReferenceUID, framereferenceID.c_str());
			string ROIName = "Anatomy";
			ROIName = ROIName + std::to_string(i + 1).c_str();
			SSRS->putAndInsertString(DCM_ROIName, ROIName.c_str());
		}
	}

	for (int j = 0; j<ContourFinalList.size(); j++){
		cout << "CPFinalList2" << j;
		if (dataset->findOrCreateSequenceItem(DCM_RTROIObservationsSequence, RROS, j).good()){
			RROS->putAndInsertString(DCM_ObservationNumber, std::to_string(j + 1).c_str());
			RROS->putAndInsertString(DCM_ReferencedROINumber, std::to_string(j + 1).c_str());
			RROS->putAndInsertString(DCM_RTROIInterpretedType, "ORGAN");
		}
	}

	for (int C1 = 0; C1<ContourFinalList.size(); C1++){
		if (dataset->findOrCreateSequenceItem(DCM_ROIContourSequence, BS, C1).good()){
			BS->putAndInsertString(DCM_ROIDisplayColor, "255\\128\\128");
			BS->putAndInsertString(DCM_ReferencedROINumber, std::to_string(C1 + 1).c_str());
			DcmItem *CS;
			for (int c = 0; c<1; c++){
				if (BS->findOrCreateSequenceItem(DCM_ContourSequence, CS, c).good()){
					CS->putAndInsertString(DCM_ContourGeometricType, "CLOSED_PLANAR");
					CS->putAndInsertString(DCM_ContourOffsetVector, "0.0\\0.0\\0.0");
					int ConPts = ContourFinalList[C1].size() / 3;
					CS->putAndInsertString(DCM_NumberOfContourPoints, std::to_string(ConPts).c_str());
					std::string str;
					for (int i3 = 0; i3<ContourFinalList[C1].size(); i3++){
						if (i3 == ContourFinalList[C1].size() - 1){
							str += std::to_string(ContourFinalList[C1].at(i3));
						}
						else{
							str += std::to_string(ContourFinalList[C1].at(i3)) + "\\";
						}
					}
					CS->putAndInsertString(DCM_ContourData, str.c_str());
					DcmItem *CIS;
					for (int c1 = 0; c1<SOPInstanceUIDList.size(); c1++){
						if (CS->findOrCreateSequenceItem(DCM_ContourImageSequence, CIS, c1).good()){
							CIS->putAndInsertString(DCM_ReferencedSOPClassUID, UID_SecondaryCaptureImageStorage);
							string SOPINS = SOPInstanceUIDList[c1];
							CIS->putAndInsertString(DCM_ReferencedSOPInstanceUID, SOPINS.c_str());
						}
					}
				}
			}
		}
	}

	dataset->putAndInsertString(DCM_PixelData, "0");


	OFCondition status;
	status = dataset->chooseRepresentation(EXS_LittleEndianExplicit, params);
	string dicomfile = fileName1;

	if (status.good()){
		fileformat.saveFile(dicomfile.c_str(), EXS_LittleEndianExplicit);
		cout << "File saved";

	}
	else
	{
		fileformat.saveFile("test.dcm", EXS_LittleEndianExplicit);
		cout << "File not saved";
	}


}