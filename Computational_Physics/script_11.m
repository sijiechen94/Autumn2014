fp=fopen('lyapunov.txt');
figure('Position',[1 1 1280 768]);
xMin=-5;
xMax=5;
filename = 'iteration.gif';
for n = 1:251
      y=fread(fp,128,'double');
      plot(y);
      axis([0 128 -5 5]);
      title(strcat(['lambda=' num2str((n-1)*0.02) ]));
      set(gca,'Position',[0.05 0.05 0.9 0.9])
      drawnow
      frame = getframe(1);
      im = frame2im(frame);
      [imind,cm] = rgb2ind(im,256);
      if n == 1;
          imwrite(imind,cm,filename,'gif', 'Loopcount',inf,'DelayTime',0.25);
      else
          imwrite(imind,cm,filename,'gif','WriteMode','append','DelayTime',0.25); 
      end
end