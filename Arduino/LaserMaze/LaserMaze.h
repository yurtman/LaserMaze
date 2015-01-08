#ifndef LaserMaze_h
#define LaserMaze_h

#include "Arduino.h"

class LaserMaze 
{	
	public:
		LaserMaze(int, int, int, int, int, int, int, int, int, int, int, int, int, int);
   		void 	Start();     				
		void 	Alarm();
		int 		GetThreshold(const int, const int);
		int 		GetRange(const int, const int);	

        boolean isaligned = false;          // are all lasers and detectors aligned?
		boolean iscalibrated = false;		// are all detectors calibrated?
        boolean isplaying = false;          // has someone entered the maze?
		boolean isactive = false;			// are all detectors calibrated?
        boolean isstealing = false;         // has someone stolen the object?
		boolean iswinner = false;			// did someone complete the maze objective?

	private:
		// functions
		void 		AlignMaze();
		void 		ActivateMaze();
		void 		PrintCalibrationValues();
		void 		CalibrateMaze();	
		void 		ResetMaze();
        void        TimerStart();
        void        TimerStop();
        void        UpdateHighscore();
        void        PrintHighscore();
        void        CheckAlignment();
        void        SendGUI();

		boolean 	DetectTrip();
		boolean	DetectSteal();

		// variables
		int m_alarm;
		int m_laser1;
		int m_laser2;
		int m_laser3;
		int m_laser4;
		int m_laser5;
		int m_portallaser;
		int m_prize;	
		int m_portaldetector;
		int m_detector1;
		int m_detector2;
		int m_detector3;
		int m_detector4 ;
		int m_detector5; 
		int m_portalthreshold = 0;
		int m_portalrange = 0;
		int m_threshold1 = 0;
		int m_range1 = 0;
		int m_threshold2 = 0;
		int m_range2 = 0;
		int m_threshold3 = 0;
		int m_range3 = 0;
		int m_threshold4 = 0;
		int m_range4 = 0;
		int m_threshold5 = 0;
		int m_range5 = 0;
        long m_StartTime;
        long m_ElapsedTime;
};

#endif
