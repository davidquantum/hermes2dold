/*** Definition of residiual vectors ***/

template<class Real, class Scalar>
Scalar Fc_euler(int n, double *wt, Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) {
	Scalar result = 0;
	Func<Scalar>* Cprev = ext->fn[0];
	Func<Scalar>* Citer = ext->fn[1];
	Func<Scalar>* phiiter = ext->fn[2];
	for (int i = 0; i < n; i++) {
		result += wt[i] * ((Citer->val[i] - Cprev->val[i]) * v->val[i] / TAU +
				D * (Citer->dx[i] * v->dx[i] + Citer->dy[i] * v->dy[i]) +
				K * Citer->val[i] * (phiiter->dx[i] * v->dx[i] + phiiter->dy[i] * v->dy[i]));
	}
	return result;
}

template<class Real, class Scalar>
Scalar Fc_cranic(int n, double *wt, Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) {
	Scalar result = 0;
	Func<Scalar>* Cprev = ext->fn[0];
	Func<Scalar>* Citer = ext->fn[1];
	Func<Scalar>* phiiter = ext->fn[2];
	Func<Scalar>* phiprev = ext->fn[3];
	for (int i = 0; i < n; i++) {
		result += wt[i] * ((Citer->val[i] - Cprev->val[i]) * v->val[i] / TAU +
				0.5 * D * (Citer->dx[i] * v->dx[i] + Citer->dy[i] * v->dy[i]) +
        0.5 * D * (Cprev->dx[i] * v->dx[i] + Cprev->dy[i] * v->dy[i]) +
				0.5 * K * Citer->val[i] * (phiiter->dx[i] * v->dx[i] + phiiter->dy[i] * v->dy[i]) +
        0.5 * K * Cprev->val[i] * (phiprev->dx[i] * v->dx[i] + phiprev->dy[i] * v->dy[i])
        );
	}
	return result;
}
template<class Real, class Scalar>
Scalar Fphi_euler(int n, double *wt, Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) {
	Scalar result = 0;
	Func<Scalar>* Citer = ext->fn[0];
	Func<Scalar>* phiiter = ext->fn[1];
	for (int i = 0; i < n; i++) {
		result += wt[i] * ((phiiter->dx[i] * v->dx[i] + phiiter->dy[i] * v->dy[i]) + 
					L * v->val[i] *(Citer->val[i] -  C_CONC));
	}
	return result;
}

// matrix 0_0
template<class Real, class Scalar>
Scalar J_euler_DFcDYc(int n, double *wt, Func<Real> *u, Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) {
	Scalar result = 0;
	Func<Scalar>* phiiter = ext->fn[0];
	for (int i = 0; i < n; i++) {
		result += wt[i] * (u->val[i] * v->val[i] / TAU +
				D * (u->dx[i] * v->dx[i] + u->dy[i] * v->dy[i]) +
				K * u->val[i] * (phiiter->dx[i] * v->dx[i] + phiiter->dy[i] * v->dy[i]));
	}
	return result;
}

template<class Real, class Scalar>
Scalar J_cranic_DFcDYc(int n, double *wt, Func<Real> *u, Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) {
	Scalar result = 0;
	Func<Scalar>* phiiter = ext->fn[0];
	Func<Scalar>* phiprev = ext->fn[1];
	for (int i = 0; i < n; i++) {
		result += wt[i] * (u->val[i] * v->val[i] / TAU +
				D * (u->dx[i] * v->dx[i] + u->dy[i] * v->dy[i]) +
				0.5 * K * u->val[i] * (phiprev->dx[i] * v->dx[i] + phiprev->dy[i] * v->dy[i]) +
				0.5 * K * u->val[i] * (phiiter->dx[i] * v->dx[i] + phiiter->dy[i] * v->dy[i]));
	}
	return result;
}


//matrix 0_1
template<class Real, class Scalar>
Scalar J_euler_DFcDYphi(int n, double *wt, Func<Real> *u, Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) {
	Scalar result = 0;
	Func<Scalar>* Citer = ext->fn[0];
	for (int i = 0; i < n; i++) {
		result += wt[i] * K * (u->dx[i] * v->dx[i] + u->dy[i] * v->dy[i]) * Citer->val[i];
	}
	return result;
}

//matrix 1_0
template<class Real, class Scalar>
Scalar J_euler_DFphiDYc(int n, double *wt, Func<Real> *u, Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) {
	Scalar result = 0;
	for (int i = 0; i < n; i++) {
		result += wt[i] * ( -L * u->val[i] * v->val[i]);
	}
	return result;
}

//matrix 1_1
template<class Real, class Scalar>
Scalar J_euler_DFphiDYphi(int n, double *wt, Func<Real> *u, Func<Real> *v, Geom<Real> *e, ExtData<Scalar> *ext) {
	Scalar result = 0;
	for (int i = 0; i < n; i++) {
		result += wt[i] * ( u->dx[i] * v->dx[i] + u->dy[i] * v->dy[i]);
	}
	return result;
}


