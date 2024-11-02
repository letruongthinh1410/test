#include "main.h"



class imp_res : public Restaurant
{
	public:	
		imp_res() {};
	// tạo struct lưu trữ tên của customer và thứ tự vào desk
	struct order_cus{
		string name;
		int energy;
		order_cus *next;
		order_cus *prev;
		order_cus(string name, int energy,order_cus *prev,order_cus *next): name(name),energy(energy), next(next),prev(prev){}
		~order_cus(){
			delete next;
		}
	};
	
	order_cus *order = NULL;
	customer* reversal_queue(customer *p){
		customer *ff = p;
		customer *nn = p->next;
		ff->next = NULL;
		ff->prev = nn;
		while(nn != NULL){
			nn->prev = nn->next; // 
			nn->next = ff;
			ff = nn;
			nn = nn->prev;
		}
		p = ff;
		return p;
	}
	//////////////////////////////////////////////////////////////////////
	// customer trong desk
	int sizeCusindesk = 0;
	customer *X = NULL;
	customer *head = NULL;
	bool flag = true;
	void add_desk(string name, int energy){
			if(order == NULL){
				order_cus *tmp = new order_cus(name,energy, NULL,NULL);
				order = tmp;
			}
			else{
				order_cus *tmp = order;
				while(tmp->next != NULL){
					tmp = tmp->next;
				}
				order_cus *tmp1 = new order_cus(name,energy,tmp,NULL);
				tmp->next = tmp1;
			}
			//neu khong co ai trong ban
			if(sizeCusindesk == 0 && flag == true){
						customer* cus = new customer(name, energy, NULL, NULL);
						X = cus;
						head = cus;
						sizeCusindesk++;
						flag = false;
					}
					else if(sizeCusindesk == 0){
						customer* cus = new customer(name, energy, NULL, NULL);
						X = cus;
						head = cus;
						sizeCusindesk++;
					}
					else{
						if(sizeCusindesk >= MAXSIZE/2){
							if(X->next == NULL){
								if(energy > 0){
								customer* cus = new customer(name, energy, X, X->next);
								if (X->next == NULL){
									X->next = cus;
									X->prev = cus;
									X = cus;
									cus->next = head;
									//////// fix loi
								}
								else{
									X->next->prev = cus;
									X->next = cus;
									X = cus;
								}
								sizeCusindesk++;
								}
								else if(energy < 0){
									customer* cus = new customer(name, energy, X->prev, X);
									if(X->prev == NULL){
										X->prev = cus;
										head ->next = cus;
										// X->next = cus;
										X = cus;
										// tao lien ket vong
									}
									else{
										X->prev->next = cus;
										X->prev = cus;
										X = cus;
									}
									sizeCusindesk++;
								}
								return;
							}
							customer *tmp = X;
							int max = 0;
							int index = 0;
							for(int i = 0; i < sizeCusindesk; i++){
								int res = abs(energy - tmp->energy);
								if(res > max){
									max = res;
									index = i;
								}
								tmp = tmp->next;
							}
							tmp = NULL;
							delete tmp;

							for(int i = 0; i < index; i++){
								X = X->next;
							}
								if(energy > 0){
									customer* cus = new customer(name, energy, X, X->next);
									X->next->prev = cus;
									X->next = cus;
									X = cus;
									sizeCusindesk++;
								}
								else if(energy < 0){
									customer* cus = new customer(name, energy, X->prev, X);
									X->prev->next = cus;
									X->prev = cus;
									X = cus;
									sizeCusindesk++;
								}
						}
						else if(sizeCusindesk < MAXSIZE/2){
							if(energy >= X->energy){
								customer* cus = new customer(name, energy, X, X->next);
								if (X->next == NULL){
									X->next = cus;
									X->prev = cus;
									X = cus;
									cus->next = head;
								}
								else{
									X->next->prev = cus;
									X->next = cus;
									X = cus;
								}
								sizeCusindesk++;
							}
							else{
								customer* cus = new customer(name, energy, X->prev, X);
								if(X->prev == NULL){
									X->prev = cus;
									head ->next = cus;
									cus->prev = head;
									//fix loi
									// X->next = cus;
									X = cus;
									 // tao lien ket vong
								}
								else{
									X->prev->next = cus;
									X->prev = cus;
									X = cus;
								}
								sizeCusindesk++;
							}
						}
					}

	}	
	
	//////////////////////////////////////////////////////////////////////
	// customer trong queue
	 customer *front = NULL;
	 customer *rear = NULL;
	 int sizeCusinqueue = 0;
	 void add_queue(string name, int energy){
			if(sizeCusinqueue == MAXSIZE)
						return;
					else{
						if(front == NULL){
							customer* cus = new customer(name, energy, NULL, NULL);
							front = cus;
							rear = cus;
							sizeCusinqueue++;
						}
						else{
							customer* cus = new customer(name, energy, NULL, NULL);
							cus->prev = rear;
							rear->next = cus;
							rear = cus;
							sizeCusinqueue++;
						}
					}
		}
	//copy queue cho queue khac
	 customer* copy_queue(customer *front){
			customer *temp = front;
			customer *new_front = NULL;
			customer *new_rear = NULL;
			for(int i = 0; i < sizeCusinqueue; i++){
				customer* cus = new customer(temp->name, temp->energy, NULL, NULL);
				if(new_front == NULL){
					new_front = cus;
					new_rear = cus;
				}
				else{
					cus->prev = new_rear;
					new_rear->next = cus;
					new_rear = cus;
				}
				temp = temp->next;
			}
			delete temp;
			return new_front;
		}
	
	//  customer *rear_p = rear;
	//////////////////////////////////////////////////////////////////////
	
	struct index_queue{
		string name;
		int energy;
		int index;
		index_queue *nx;
		index_queue(string name,int energy,int index,index_queue *nx ):name(name),energy(energy),index(index),nx(nx){}
		~index_queue(){
			delete nx;
		}
	};

	// sap xep customer trong queue theo gia tri tuyet doi cua energy	
	int shell_sort_queue(customer *frt , int size , index_queue *hd){
		if(front == NULL || front->next == NULL)
				return 0;
				// index
		int count = 0;
		for(int gap = size/2; gap > 0; gap /= 2){
			for(int i = gap; i < size; i++){
				customer *tps = frt;
				int j = i;
				int r1 = i;
				while(r1){
					tps = tps->next;
					r1--;	
				}
				int tpse = tps->energy;
				string tpsn = tps->name;
				int r2 = j-gap;
				customer *tpt = frt;
				while(r2){
					tpt = tpt->next;
					r2--;
				}
				while(j >= gap && abs(tpt->energy) <= abs(tpse)){
					if(abs(tpt->energy) == abs(tpse)){
						int indext = 0;
						int indexs = 0;
						index_queue *tpp = hd;
						for(int i = 0 ; i <size;i++){
							if(tpt->name == tpp->name){
								indext = tpp->index;
							}
							if(tpsn == tpp->name){
								indexs = tpp->index;
							}
							tpp = tpp->nx;
						}
						count++;
						if(indext < indexs){
							break;
						}
					}
					tps->energy = tpt->energy;
					tps->name = tpt->name;
					int rt = j - gap*2;
					int rs = j - gap;
					customer *tpt1 = frt;
					customer *tps1 = frt;
					while(rt > 0){
						tpt1 = tpt1->next;
						rt--;
					}
					tpt = tpt1;
					while(rs){
						tps1 = tps1->next;
						rs--;
					}
					tps = tps1;	
					j -= gap;
					count ++;
				}
				r2 = j;
				tpt = frt;
				while(r2){
					tpt = tpt->next;
					r2--;
				}
				tpt->energy = tpse;
				tpt->name = tpsn;
				// 		customer *tpp = frt;	
				// for(int i = 0 ; i <size;i++){
				// 	cout<< tpp->name<<" "<<tpp->energy<<"  ";
				// 	tpp= tpp->next;
				// }
				// cout<<endl;

				}
			
		}
		// customer *tp = frt;	
		// cout<<"resul ";
		// for(int i = 0 ; i <size;i++){
		// 	cout<< tp->name<<" "<<tp->energy<<"  ";
		// 	tp = tp->next;
		// }
		// cout<<count<<endl;
		return count;
	}
	
	//////////////////////////////////////////////////////////////////////
	// void delete_customer(customer *p){
		// if(p->next == NULL){
		// 	p->prev->next = NULL;
		// 	p->prev = NULL;
		// 	sizeCusindesk--;
		// }
		// else if(p->prev == NULL){
		// 	p->next->prev = NULL;
		// 	p->next = NULL;
		// 	sizeCusindesk--;
		// }
		// else{
		// 	p->next->prev = p->prev;
		// 	p->prev->next = p->next;
		// 	sizeCusindesk--;
		// }
	// }

	//////////////////////////////////////////////////////////////////////	
	void RED(string name, int energy){
		// cout<<"RED"<<endl;
			//khong phai  thuật sư hoặc oán linh
			if(energy == 0)
				return;
			//neu MAXSIZE max va hang doi full
			else if(energy != 0){
				if(sizeCusindesk == MAXSIZE && sizeCusinqueue == MAXSIZE)
					return;
				//"thiên thượng thiên hạ, duy ngã độc tôn"
				customer *temp = head;
				for(int i = 0; i < sizeCusindesk; i++){
					if(temp->name == name)
						return;
					temp = temp->next;
				}
				temp = front;
				for(int i = 0; i < sizeCusinqueue; i++){
					if(temp->name == name)
						return;
					temp = temp->next;
				}
				temp = NULL;
				delete temp;
				if(sizeCusindesk < MAXSIZE){
					add_desk(name, energy);
				}
				// thêm vào queue
				else{
					add_queue(name, energy);
				}
			}
			
			// customer *tp =X ;
			// for(int i = 0; i < sizeCusindesk; i++){
			// 	cout << tp->name << " " << tp->energy << " ";
			// 	tp = tp->prev;
			// }
			// cout<<endl;
			// tp = X;
			// for(int i = 0; i < sizeCusindesk; i++){
			// 	cout << tp->name << " " << tp->energy << " ";
			// 	tp = tp->next;
			// }
			// cout<<endl;

			// tp = NULL;
			// free(tp);

		}

/////////////////////////////////////////////////////////////////////////
		void BLUE(int num)
		{
			// cout<<"BLUE"<<endl;
			if(num >= sizeCusindesk || num >= MAXSIZE)
				num = sizeCusindesk;
			// xoa trong desk	
			customer *temp = X;
			for(int i = 0; i < num;i++){
				if(sizeCusindesk == 0)
					break;
				while(temp){
					if(temp->name == order->name){
						order = order->next;
						temp->next->prev = temp->prev;
						temp->prev->next = temp->next;
						sizeCusindesk--;
						break;
					}
					temp = temp->next;
				}
			}
			if(temp->energy > 0){
				if(temp->next == NULL)
					return;
				X = temp->next;
			}
			else if(temp->energy < 0){
				if(temp->prev == NULL)
					return;
				X = temp->prev;
			}
			temp = NULL;
			delete temp;	
			//xoa trong queue
			head = X;
			for(int i = 0; i < num; i++){
				if(sizeCusindesk < MAXSIZE){
					if(sizeCusinqueue == 0)
						break;
					add_desk(front->name, front->energy);
					front = front->next;
					sizeCusinqueue--;
				}
				else
					break;
			}
			
			// customer *tp;
			// tp = X;
			// cout<<"sau ";
			// for(int i = 0 ;i< sizeCusindesk;i++){
			// 	cout<< tp->name<<" "<<tp->energy<<"  ";
			// 	tp = tp->next;
			// }		
		}

/////////////////////////////////////////////////////////////////////////
		
		void PURPLE()
		{
			// cout<<"PURPLE"<<endl;
			customer *front_p = copy_queue(front);
			int size_copy_queue = sizeCusinqueue;
			int idx = 0;
			int max = 0;
			customer *tm = front_p;
			index_queue *hd = NULL;
			for(int i = 1 ; i < sizeCusinqueue+1;i++){
				if(hd == NULL){
					index_queue *tmp = new index_queue(tm->name,tm->energy,i,NULL);
					hd = tmp;
				}
				else{
					index_queue *tmp = hd;
					while(tmp->nx != NULL){
						tmp = tmp->nx;
					}
					index_queue *tmp1 = new index_queue(tm->name,tm->energy,i,NULL);
					tmp->nx = tmp1;
				}
				if(max <= abs(tm->energy)){
					max = abs(tm->energy);
					idx = i;
				}
				tm = tm->next;
			}
				// customer *tpp = front;
				// for(int i = 0 ; i< sizeCusinqueue;i++){
				// 	cout<<tpp->name<<" "<<tpp->energy<<" ";
				// 	tpp = tpp->next;
				// }
				// cout<<endl;
				int count = shell_sort_queue(front,idx,hd);
				// cout<<count<<endl;
				// tpp =  front;
				// for(int i = 0 ; i< sizeCusinqueue;i++){
				// 	cout<<tpp->name<<" "<<tpp->energy<<" ";
				// 	tpp = tpp->next;
				// }
				int nmm = count%MAXSIZE;
				BLUE(nmm);
				delete hd;
				delete tm;
				delete front_p;
		}

/////////////////////////////////////////////////////////////////////////
		void REVERSAL()
		{
			// cout<<"REVERSAL"<<endl;
			if(sizeCusindesk <= 1){
				return;
			}
			customer *temp = X;
			customer *front_chu = NULL;
			customer *front_oan = NULL;
			customer *pp = X ;
			string name_X = X->name;
					// for(int i = 0 ;i<sizeCusindesk;i++){
					// 	cout<<pp->name<<" "<<pp->energy<<" ";
					// 	pp =pp->prev;
					// }
					// cout<<endl;
			for(int i = 0;i < sizeCusindesk;i++){
				if(temp->energy > 0){
					if(front_chu == NULL){
						customer *tmp = new customer(temp->name,temp->energy,NULL,NULL);
						front_chu = tmp;
					}
					else{
						customer *tmp = front_chu;
						while(tmp->next != NULL){
							tmp = tmp->next;
						}
						customer *tmp1 = new customer(temp->name,temp->energy,tmp,NULL);
						tmp->next = tmp1;
					}
				}
				else if(temp->energy < 0){
					if(front_oan == NULL){
						customer *tmp = new customer(temp->name,temp->energy,NULL,NULL);
						front_oan = tmp;
					}
					else{
						customer *tmp = front_oan;
						while(tmp->next != NULL){
							tmp = tmp->next;
						}
						customer *tmp1 = new customer(temp->name,temp->energy,tmp,NULL);
						tmp->next = tmp1;
					}
				}
				temp = temp->prev;
			}
			customer *tpp = front_chu;
						// while(tpp!= NULL){
						// 	cout<<tpp->name<<" "<<tpp->energy<<" ";
						// 	tpp = tpp->next;
						// }
						// cout<<endl;
			front_chu = reversal_queue(front_chu);
			tpp = front_chu;
						// while(tpp != NULL){
						// 	cout<<tpp->name<<" "<<tpp->energy<<" ";
						// 	tpp = tpp->next;
						// }
						// cout<<endl;
						// tpp = front_oan;
						// while(tpp != NULL){
						// 	cout<<tpp->name<<" "<<tpp->energy<<" ";
						// 	tpp = tpp->next;
						// }
						// cout<<endl;
			front_oan = reversal_queue(front_oan);
			
						// tpp = front_oan;
						// while(tpp != NULL){
						// 	cout<<tpp->name<<" "<<tpp->energy<<" ";
						// 	tpp = tpp->next;
						// }
						// cout<<endl;
			for(int i = 0;i < sizeCusindesk;i++){
				if(temp->energy > 0){
					temp->name = front_chu->name;
					temp->energy = front_chu->energy;
					front_chu = front_chu->next;
				}
				else if(temp->energy < 0){
					temp->name = front_oan->name;
					temp->energy = front_oan->energy;
					front_oan = front_oan->next;
				}
				temp = temp->prev;
			}	

			customer *tp = X;
			while(tp){
				if(name_X == tp->name){
					X = tp;
					break;
				}
				tp = tp->next;
			}
					// tp = X;
					// cout<<"resul reversal ";
					// for(int i = 0 ; i <sizeCusindesk;i++){
					// cout<< tp->name<<" "<<tp->energy<<"  ";
					// tp = tp->prev;	
					// }
					// cout<<endl;
			// temp = NULL;
			// delete temp;
		}

////////////////////////////////////////////////////////////////////////
		
		void UNLIMITED_VOID()
		{
			// cout<<"UNLIMITED_VOID"<<endl;
			int num = 0;
			int init = 0;
			int end = 0;
			
			if(sizeCusindesk < 4)
				return;
				////////
			int min = X->energy;
			for(int i = 4 ; i<sizeCusindesk;i++){
				for(int j = 0; j<sizeCusindesk;j++){
					int tmj = j;
					customer *tmp = X;
					while(tmj){
						tmp = tmp->next;
						tmj--;
					}
					int tm_min = 0;
					for(int k = 0; k<i;k++){
						tm_min += tmp->energy;
						tmp = tmp->next;
					}
					if(tm_min <= min){
						min = tm_min;
						init = j;
						end = j+i;
						num = i;
					}
				}
			}
			// cout<<init<<" "<<end<<" "<<num<<endl;
			customer *tp = X;
			for(int i = 0 ; i <init;i++){
				tp = tp->next;
			}
			customer *head_min = NULL;
			for(int i = init ; i <= end;i++){
				if(head_min == NULL){
					customer *tmp = new customer(tp->name,tp->energy,NULL,NULL);
					head_min = tmp;
				}
				else{
					customer *tmp = head_min;
					while(tmp->next != NULL){
						tmp = tmp->next;
					}
					customer *tmp1 = new customer(tp->name,tp->energy,tmp,NULL);
					tmp->next = tmp1;
				}
				tp = tp->next;
			}
			customer *tmm = head_min;
			tmm = head_min;
			while(tmm->next != NULL){
				tmm = tmm->next;
			}
			tmm->next = head_min;
			head_min->prev = tmm;
			// tim vi tri min trong head_min
			int index_min = 0;
			customer *tpp = head_min;
			int min_min = head_min->energy;
			for(int i = 0 ; i <num;i++){
				if(min_min > tpp-> energy){
					min_min = tpp->energy;
					index_min = i;
				}
				tpp = tpp->next;
			}
			tpp = head_min;
			while(index_min){
				tpp = tpp->next;
				index_min --;
			}
			for(int i = 0;i<num;i++){
				tpp->print();
				tpp = tpp->next;
			}


		}		// 

/////////////////////////////////////////////////////////////////////////
		void DOMAIN_EXPANSION()
		{
			// cout<<"DOMAIN_EXPANSION"<<endl;
			int sum_chu = 0;
			int sum_oan = 0;
			int sum_tong = 0;
			customer *tmp = X;
			customer *delete_list = NULL;
			// tinh tong energy trong desk
			for(int i = 0 ; i < sizeCusindesk;i++){
				if(tmp->energy > 0){
					sum_chu += tmp->energy;
				}
				else if(tmp->energy < 0){
					sum_oan += abs(tmp->energy);
				}
				sum_tong += tmp->energy;
				tmp = tmp->next;
			}
			// tinh tong energy trong queue
			customer *tmp1 = front;
			for(int i = 0 ; i < sizeCusinqueue;i++){
				if(tmp1->energy > 0){
					sum_chu += tmp1->energy;
				}
				else if(tmp1->energy < 0){
					sum_oan += abs(tmp1->energy);
				}
				sum_tong += tmp1->energy;
				tmp1 = tmp1->next;
			}
			// chu thuat su
			// cout<<sum_chu<<" "<<sum_oan<<" "<<sum_tong<<endl;
			if(sum_chu >= abs(sum_tong)){
				customer *tmp = X;
				order_cus *tmp2 = order;
				// for(int i = 0 ; i<sizeCusindesk ; i++){
				// 	cout<<tmp2->name<<" "<<tmp2->energy<<" ";
				// 	tmp2= tmp2->next;
				// }
				int sizeCusindesk_tmp = sizeCusindesk;
				for(int i = 0 ; i < sizeCusindesk_tmp;i++){
					// cout<<tmp2->name<<" "<<tmp2->energy<<" ";
					if(tmp2->energy < 0){
						tmp = X;
						while(tmp->name != tmp2->name){
							tmp = tmp->next;
						}
							if(delete_list == NULL){
								customer *tmp1 = new customer(tmp->name,tmp->energy,NULL,NULL);
								delete_list = tmp1;
							}
							else{
								customer *tmp1 = delete_list;
								while(tmp1->next != NULL){
									tmp1 = tmp1->next;
								}
								customer *tppp = new customer(tmp->name,tmp->energy,tmp1,NULL);
								tmp1->next = tppp;
							}
								// xoa trong desk
								if(tmp->next == NULL){
									tmp->prev->next = NULL;
									tmp->prev = NULL;
									sizeCusindesk--;
								}
								else if(tmp->prev == NULL){
									tmp->next->prev = NULL;
									tmp->next = NULL;
									sizeCusindesk--;
								}
								else{
									tmp->next->prev = tmp->prev;
									tmp->prev->next = tmp->next;
									sizeCusindesk--;
								}
								if(tmp->energy > 0){
									if(tmp->next == NULL)
										return;
									X = tmp->next;
								}
								else if(tmp->energy < 0){
									if(tmp->prev == NULL)
										return;
									X = tmp->prev;
								}
								//xoa trong order
								if(tmp2->next == NULL){
									tmp2->prev->next = NULL;
									tmp2->prev = NULL;
									tmp2 = tmp2->next;
								}
								else if(tmp2->prev == NULL){
									tmp2->next->prev = NULL;
									order_cus *tmp3 = tmp2->next;
									tmp2->next = NULL;
									tmp2 = tmp3;
								}
								else{
									tmp2->next->prev = tmp2->prev;
									tmp2->prev->next = tmp2->next;
									tmp2 = tmp2->next;
								}
						
					}
					else{
						tmp2 = tmp2->next;
					}
				}	
				customer *tm_front = front;
				int sizeCusinqueue_tmp = sizeCusinqueue;
				for(int i = 0 ; i < sizeCusinqueue_tmp;i++){
					if(tm_front->energy < 0){
							if(delete_list == NULL){
								customer *tmp1 = new customer(tm_front->name,tm_front->energy,NULL,NULL);
								delete_list = tmp1;
							}
							else{
								customer *tmp1 = delete_list;
								while(tmp1->next != NULL){
									tmp1 = tmp1->next;
								}
								customer *tmp2 = new customer(tm_front->name,tm_front->energy,tmp1,NULL);
								tmp1->next = tmp2;
							}
							if(tm_front->next == NULL){
								tm_front->prev->next = NULL;
								tm_front->prev = NULL;
								sizeCusinqueue--;
								tm_front = tm_front->next;
							}
							else if(tm_front->prev == NULL){
								tm_front->next->prev = NULL;
								customer *tmmp3 = tm_front->next;
								tm_front->next = NULL;
								tm_front = tmmp3;
								front = tmmp3;
								sizeCusinqueue--;
							}
							else{
								tm_front->next->prev = tm_front->prev;
								tm_front->prev->next = tm_front->next;
								sizeCusinqueue--;
								tm_front = tm_front->next;
							}
					}
					else{
						tm_front = tm_front->next;
					}
					
				}
			
			}
			// customer *tpp = delete_list;
			// int c =0;
			// while(tpp){
			// 	tpp->print();
			// 	tpp = tpp->next;
			// 	c++;
			// }
			// cout<<c<<endl;
		//oan linh
		else{
			 order_cus *tmmp2 = order;
			 int sizeCusindesk_tmp = sizeCusindesk;
			 for(int i = 0; i < sizeCusindesk_tmp ; i++){
					if(tmmp2->energy > 0){
						 customer *tmmp = X ;
						while(tmmp->name != tmmp2->name){
							tmmp = tmmp->next;
						}
						if(delete_list == NULL){
							customer *tmmp1 = new customer(tmmp->name,tmmp->energy,NULL,NULL);
							delete_list = tmmp1;
						}
						else{
							customer *tmmp1 = delete_list;
							while(tmmp1->next != NULL){
								tmmp1 = tmmp1->next;
							}
							customer *tmmp2 = new customer(tmmp->name,tmmp->energy,tmmp1,NULL);
							tmmp1->next = tmmp2;
						}
						// xoa trong desk
						if(tmmp->next == NULL){
							tmmp->prev->next = NULL;
							tmmp->prev = NULL;
							sizeCusindesk--;
						}
						else if(tmmp->prev == NULL){
							tmmp->next->prev = NULL;
							tmmp->next = NULL;
							sizeCusindesk--;
						}
						else{
							tmmp->next->prev = tmmp->prev;
							tmmp->prev->next = tmmp->next;
							sizeCusindesk--;
						}
						if(tmmp->energy > 0){
							if(tmmp->next == NULL)
								return;
							X = tmmp->next;
						}
						else if(tmmp->energy < 0){
							if(tmmp->prev == NULL)
								return;
							X = tmmp->prev;
						}
						cout<<	tmmp2->next->prev->energy<<" "<<tmmp2->next->prev->name<<" ";
						//xoa trong order
						if(tmmp2->next == NULL){
							tmmp2->prev->next = NULL;
							tmmp2->prev = NULL;
							tmmp2 = tmmp2->next;
						}
						else if(tmmp2->prev == NULL){
							tmmp2->next->prev = NULL;
							order_cus *tmmp3 = tmmp2->next;
							tmmp2->next = NULL;
							tmmp2 = tmmp3;
						}	
						else{
							tmmp2->next->prev = tmmp2->prev;
							tmmp2->prev->next = tmmp2->next;
							tmmp2 = tmmp2->next;
						}
						}
						else{
							tmmp2 = tmmp2->next;
						}	
					}
					customer *tm_front = front;
					int sizeCusinqueue_tmp = sizeCusinqueue;
					for(int i = 0 ; i < sizeCusinqueue_tmp;i++){
						if(tm_front->energy > 0){
								if(delete_list == NULL){
									customer *tmp1 = new customer(tm_front->name,tm_front->energy,NULL,NULL);
									delete_list = tmp1;
								}
								else{
									customer *tmp1 = delete_list;
									while(tmp1->next != NULL){
										tmp1 = tmp1->next;
									}
									customer *tmp2 = new customer(tm_front->name,tm_front->energy,tmp1,NULL);
									tmp1->next = tmp2;
								}
								if(tm_front->next == NULL){
									tm_front->prev->next = NULL;
									tm_front->prev = NULL;
									sizeCusinqueue--;
									tm_front = tm_front->next;
								}
								else if(tm_front->prev == NULL){
									tm_front->next->prev = NULL;
									customer *tmmp3 = tm_front->next;
									tm_front->next = NULL;
									tm_front = tmmp3;
									front = tmmp3;
									sizeCusinqueue--;
								}
								else{
									tm_front->next->prev = tm_front->prev;
									tm_front->prev->next = tm_front->next;
									sizeCusinqueue--;
									tm_front = tm_front->next;
								}
						}
						else{
							tm_front = tm_front->next;
						}
			 		}
				
		}
		
			// cout<<sizeCusindesk<<" "<<sizeCusinqueue<<endl;
			//  cout<<endl;
			
			customer* tpp ;
			// tpp = X;
			// for(int i = 0 ; i < sizeCusindesk;i++){
			// 	cout<<" X "<<tpp->name<<" "<<tpp->energy<<" ";
			// 	tpp = tpp->next;
			// }
			//  cout<<endl;
			// tpp = front;
			// for(int i = 0 ; i < sizeCusinqueue;i++){
			// 	cout<<" queue "<<tpp->name<<" "<<tpp->energy<<" ";
			// 	tpp = tpp->next;
			// }
			// cout<<endl;

			tpp = delete_list;
			while(tpp){
				tpp->print();
				tpp = tpp->next;
			 }
		}
	
	/////////////////////////////////////////////////////////////////////////
		void LIGHT(int num)
		{
			// cout<<"LIGHT"<<endl;
			customer *tm_front = front;
			customer *tm_X = X;
			if(num == 0){
				for(int i = 0 ; i < sizeCusinqueue ; i++){
					tm_front->print();
					tm_front = tm_front->next;
				}
			}
			else if(num > 0){
				for(int i = 0 ; i < sizeCusindesk ; i++){
					tm_X->print();
					tm_X = tm_X->next;
				}
			}
			else if(num < 0){
				for(int i = 0 ; i < sizeCusindesk ; i++){
					tm_X->print();
					tm_X = tm_X->prev;
				}
			}
			
		}
		
		

//////////////////////////////////////////////////////////////////////////

		~imp_res() {
			// delete head;
			delete order;
			delete X;
			delete front;
			delete rear;
			// free(head);
			// free(order);
			// free(X);
			// free(front);
			// free(rear);

		}
};