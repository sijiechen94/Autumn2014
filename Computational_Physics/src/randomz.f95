! A subrontine for generating random number      
      subroutine randomz(ia,ib,x)
      implicit none
      integer :: ia,ib
      real*8 :: x
      integer,save:: initial(15)
      real*8 ,save:: iy(15),iz=100000001.d0
 
      selectcase(ia)
      case(1)
! Loading seeds from stdin
        read(*,*) initial
        iy=dble(initial)
        x=iy(ib)*1.0d-8
! Generate next random number
      case(2)
        iy(ib)=mod(329.d0*iy(ib),iz)
        x=iy(ib)*1.0d-8
! Reset the seeds
      case(3) 
        iy=dble(initial)
      endselect
      end subroutine randomz

! Driver
      program main
      implicit none
      integer ia,ib
      double precision x
      integer ii
      
      ia=1
      ib=1
      x=0.3
! Set the seeds
      call randomz(ia,ib,x)
      print "(f10.8)", x 
      ia=2
! Generate a total of 1e7 random number
      do ii=2,10000000
        call randomz(ia,ib,x)
! This program run significantly slower than Schrage in C
! The following line has caused this instead of the subroutine
        print "(f10.8)", x 
      enddo
      end program main
