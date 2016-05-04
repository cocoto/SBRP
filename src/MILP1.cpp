#include "gurobi_c++.h"
#include "Solution.hpp"
#include <sstream>
using namespace std;

int Solution::milp_assignment ()
{
	GRBEnv* env = 0;
	GRBVar** x = 0;
	GRBVar* y = 0;

	int xCt = 0;
	try
	{
		int n_students = instance->get_num_students();
		int n_stops = instance->get_num_stops();
		int* Students=new int[n_students];
		for(int i=0; i<n_students; i++){
			Students[i]=i;
		}

		int* BusStops = new int[n_stops];
		for(int i=0; i<n_stops; i++){
			BusStops[i]=i;
		}


		// Model
		env = new GRBEnv();
		GRBModel model = GRBModel(*env);
		// model.set(GRB_StringAttr_ModelName, "");

		// Assignment variables: x[i][k] == 1 if student i is assigned
		// to bus stop k. Since an assignment model always produces integer
		// solutions, we use continuous variables and solve as an LP.
		x = new GRBVar*[n_students];
		for (int i = 0; i < n_students; i++)
		{
			//x[i] = model.addVars(, GRB.BINARY);
			xCt++;
			model.update();
			x[i]=new GRBVar[n_stops];
			for (int k = 0; k < n_stops; k++)
			{
				ostringstream vname;
				vname << Students[i] << "." << BusStops[k];
				x[i][k]=model.addVar(0.0,1.0,0.0,GRB_BINARY, vname.str());
				//x[i][k].set(GRB_DoubleAttr_Obj,0);
				//x[i][k].set(GRB_StringAttr_VarName, vname.str());
			}
		}
		cout<<"hello1"<<endl;
		model.update();
		cout<<"hello1.5"<<endl;
		// Assignment variables: y[k] == 1 if the bus stop k is used.
		// Since an assignment model always produces integer
		// solutions, we use continuous variables and solve as an LP.
		y = new GRBVar[n_stops];

		for (int k = 0; k < n_stops; k++)
		{

			model.update();
			ostringstream vname1;
			vname1 << BusStops[k];
			y[k]=model.addVar(0.0,1.0,1.0,GRB_BINARY, vname1.str());
			//y[k].set(GRB_DoubleAttr_Obj,1);
			//y[k].set(GRB_StringAttr_VarName, vname1.str());


		}

		model.update();
		cout<<"hello2"<<endl;
		// The objective is to minimize the total number of stops
		model.set(GRB_IntAttr_ModelSense, 1);

		// Update model to integrate new variables
		model.update();

		// Constraint 1:
		for (int i = 0; i < n_students; i++)
		{
			GRBLinExpr lhs1 = 0;
			for (int k = 0; k < n_stops; k++)
			{
				lhs1 += instance->get_dist_student_stop(i,k) * x[i][k];
			}
			model.addConstr(lhs1 <= instance->get_max_dist_stop());
		}
		model.update();


		//Constraint 2:
		for (int i = 0; i < n_students; i++)
		{
			GRBLinExpr lhs2 = 0;
			for (int k = 0; k < n_stops; k++)
			{
				lhs2 += x[i][k];
			}
			model.addConstr(lhs2 == 1);
		}

		//Constraint 3:
		for (int k = 0; k < n_stops; k++)
		{
			GRBLinExpr lhs3 = 0;
			for (int i = 0; i < n_students; i++)
			{
				lhs3 += instance->get_student(i)->getWeight() *x[i][k];
			}
			model.addConstr(lhs3 <= instance->get_cap_buses());
		}


		//Constraint 4:
		for (int i = 0; i < n_students; i++)
		{

			for (int k = 0; k < n_stops; k++)
			{
				GRBLinExpr lhs4 = 0;
				lhs4 = x[i][k]-y[k];
				model.addConstr(lhs4 <=0);
			}

		}

		model.update();
		cout<<"hello"<<endl;
		// Optimize
		model.optimize();


		int status = model.get(GRB_IntAttr_Status);
		if (status == GRB_UNBOUNDED)
		{
			cout << "The model cannot be solved "
					<< "because it is unbounded" << endl;
			//return 1;
		}
		if (status == GRB_OPTIMAL)
		{
			cout << "The optimal objective is " <<
					model.get(GRB_DoubleAttr_ObjVal) << endl;

		}
		if ((status != GRB_INF_OR_UNBD) && (status != GRB_INFEASIBLE))
		{
			cout << "Optimization was stopped with status " << status << endl;
			//return 1;
		}
		cout << "OK" << endl;
		assignments->remove_all_assignments();
		for (int t = 0; t < n_students; ++t) {
			for (int h = 0; h < n_stops; ++h) {
			//cout << x[t][h].get(GRB_DoubleAttr_X) << endl;
				if(x[t][h].get(GRB_DoubleAttr_X) >= 0.9){
					cout<<"Assign students "<<t<<" to stop "<<h<<endl;
					assignments->assign_student_stop(t, h);
				}
			}
		}


		// do IIS
		//    cout << "The model is infeasible; computing IIS" << endl;
		//    model.computeIIS();
		//    cout << "\nThe following constraint(s) "
		//    << "cannot be satisfied:" << endl;
		//    c = model.getConstrs();
		//    for (int i = 0; i < model.get(GRB_IntAttr_NumConstrs); ++i)
		//    {
		//      if (c[i].get(GRB_IntAttr_IISConstr) == 1)
		//      {
		//        cout << c[i].get(GRB_StringAttr_ConstrName) << endl;
		//      }
		//    }

		delete[] Students;
		delete[] BusStops;


	}
	catch (GRBException e)
	{
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...)
	{
		cout << "Exception during optimization" << endl;
	}

	delete[] y;
	for (int i = 0; i < xCt; ++i) {
		delete[] x[i];
	}
	delete[] x;

	delete env;

	return 0;
}
