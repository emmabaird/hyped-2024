import {
  Binary,
  Copy,
  HardDriveUpload,
  MoreHorizontal,
  Settings,
  Terminal,
} from 'lucide-react';
import { Button } from '@/components/ui/button';
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuLabel,
  DropdownMenuSeparator,
  DropdownMenuTrigger,
} from '@/components/ui/dropdown-menu';
import { Row } from '@tanstack/react-table';
import { PiWithVersion } from '@hyped/telemetry-types';

export const ActionsMenu = ({ row }: { row: Row<PiWithVersion> }) => {
  const pi = row.original;

  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild>
        <Button variant="ghost" className="h-8 w-8 p-0">
          <span className="sr-only">Open menu</span>
          <MoreHorizontal className="h-4 w-4" />
        </Button>
      </DropdownMenuTrigger>
      <DropdownMenuContent align="end">
        <DropdownMenuLabel>Actions</DropdownMenuLabel>
        <DropdownMenuItem
          className="flex gap-2"
          onClick={() => navigator.clipboard.writeText(pi.ip)}
        >
          <Copy size={18} />
          Copy IP address
        </DropdownMenuItem>
        <DropdownMenuItem className="flex gap-2">
          <Terminal size={18} />
          SSH into Pi
        </DropdownMenuItem>
        <DropdownMenuSeparator />
        <DropdownMenuLabel>Update</DropdownMenuLabel>
        <DropdownMenuItem className="flex gap-2">
          <Binary size={18} />
          Update Binary
        </DropdownMenuItem>
        <DropdownMenuItem className="flex gap-2">
          <Settings size={18} />
          Update Config
        </DropdownMenuItem>
        <DropdownMenuItem className="flex gap-2">
          <HardDriveUpload size={18} />
          Update All
        </DropdownMenuItem>
      </DropdownMenuContent>
    </DropdownMenu>
  );
};